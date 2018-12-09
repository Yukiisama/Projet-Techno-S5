#include "ei_draw.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


static inline ei_color_t alpha_blend(const ei_color_t in_pixel, const ei_color_t dst_pixel)
{
    ei_color_t blended;
    float src_alpha = ((float)in_pixel.alpha) / 255.f;
    float dst_alpha = ((float)dst_pixel.alpha) / 255.f;

    blended.alpha = (int)(255 * ((1.f -  src_alpha) * dst_alpha  + src_alpha));

    if(blended.alpha == 0) {
        blended.red = 0;
        blended.green = 0;
        blended.blue = 0;
    }else{
        blended.red   = (int)((1.f -  src_alpha) * dst_pixel.red     + src_alpha * in_pixel.red);
        blended.green = (int)((1.f -  src_alpha) * dst_pixel.green + src_alpha * in_pixel.green);
        blended.blue  = (int)((1.f -  src_alpha) * dst_pixel.blue   + src_alpha * in_pixel.blue);
    }
    return blended;
}


void ei_draw_line_correction(ei_surface_t surface, const ei_point_t start,
                  const ei_point_t end, const ei_color_t color)
{
    ei_point_t pos = start;
    int dx, dy;
    int stepx, stepy;
    dx = end.x - pos.x;
    dy = end.y - pos.y;
    if (dy < 0) { dy = -dy; stepy = -1; } else { stepy = 1; }
    if (dx < 0) { dx = -dx; stepx = -1; } else { stepx = 1; }
    dy <<= 1; /* dy is now 2*dy */
    dx <<= 1; /* dx is now 2*dx */
    hw_put_pixel(surface, pos, color);
    if (dx > dy) {
        int fraction = dy - (dx >> 1);
        while (pos.x != end.x) {
            pos.x += stepx;
            if (fraction >= 0) {
                pos.y += stepy;
                fraction -= dx;
            }
            fraction += dy;
            hw_put_pixel(surface, pos, color);
        }
    } else {
        int fraction = dx - (dy >> 1);
        while (pos.y != end.y) {
            if (fraction >= 0) {
                pos.x += stepx;
                fraction -= dy;
            }
            pos.y += stepy;
            fraction += dx;
            hw_put_pixel(surface, pos, color);
        }
    }
}


int ei_draw_polyline_correction(ei_surface_t surface,
                 const ei_linked_point_t* first_point,
                 const ei_color_t color)
{
    ei_point_t start, end;

    if (first_point == NULL)
        return 1;

    start = first_point->point;
    while (first_point->next != NULL) {
        end = first_point->next->point;
        ei_draw_line_correction(surface, start, end, color);
        start = end;
        first_point = first_point->next;
    }
    return 0;
}


/**
 * \brief   Compute min and max scanline (in the y direction) for the given polygon
 *
 * @param   first_point     The head of a linked list of the points of the polygon.
 * @param   min_scanline    Stores the minimum scanline
 * @param   max_scanline    Stores the maximum scanline
 */
void min_max_scanline(const ei_linked_point_t* first_point, int* min_scanline, int* max_scanline)
{
    /* TO BE COMPLETED */
}

/**
 * \brief   Allocate and store all edges of the polygon into an edge_table (ei_edge_t)
 *          in the increasing order of y and x.
 *          For example, edge_table[current_scanline] contains all edges for which
 *          lowest y position is current_scanline + min_scanline
 *
 * @param   first_point     The head of a linked list of the points of the polygon.
 * @param   min_scanline    The minimum scanline
 */
ei_edge_t** build_edge_table(const ei_linked_point_t* first_point, int min_scanline, int max_scanline)
{
    // Allocate the edge table and initialize all its entries to NULL
    ei_edge_t** edge_table;
    /* TO BE COMPLETED */

    // Fill edge table
    ei_point_t start = first_point->point;
    const ei_linked_point_t* lpoint = first_point->next;
    ei_bool_t all_processed = EI_FALSE;
    int current_scanline;

    // Process polygon edges one by one
    while (!all_processed) {
        if (lpoint == NULL) {
            lpoint = first_point;
            all_processed = EI_TRUE;
        }

        ei_point_t end = lpoint->point;
        // skip horizontal edges
        if (start.y != end.y) {
            // Allocate current_edge and fill its fields: y_max, x_min, inv_m
            ei_edge_t* current_edge;  /* TO BE COMPLETED */
            if (start.y < end.y) {
                /* TO BE COMPLETED */
                current_scanline = start.y - min_scanline;
            } else {
                 /* TO BE COMPLETED */
                current_scanline = end.y - min_scanline;
            }

            ei_edge_t* prev_edge = edge_table[current_scanline];

            // Insert current_edge in edge table sorted by increasing x of the lower end
            if (prev_edge == NULL) {
                // no prev_edge => insert curent_edge in edge_table[current_scanline]
                 /* TO BE COMPLETED */
            } else {
                // current_edge x_min superior => iterate over the list and find correct insertion position
                /* TO BE COMPLETED */
            }
        }
        // Process next edge
        start = end;
        lpoint = lpoint->next;
    }

    return edge_table;
}

/**
 * @brief Debugging functions to print the edge tables
 */
void print_edge_table_entry(ei_edge_t* edge)
{
    while (edge != NULL) {
        printf("[%d, %f, %f] ", edge->y_max, edge->x_min, edge->inv_m);
        edge = edge->next;
    }
    printf("\n");
}

void print_edge_table(ei_edge_t** edge_table, int min_scanline, int max_scanline)
{
    ei_edge_t* current_edge;
    printf("Edge table:\n");
    for (int i = 0; i <= (max_scanline - min_scanline); i++) {
        if (edge_table[i] != NULL) {
            printf("%d: ", i + min_scanline);
            current_edge = edge_table[i];
            print_edge_table_entry(current_edge);
        }
    }
    printf("\n");
}


int ei_draw_polygon(ei_surface_t surface, const ei_linked_point_t* first_point,
                    const ei_color_t color)
{
    if (first_point == NULL) {
        fprintf(stderr, "no point for the polygon\n");
        return 1;
    }

    /* Step 1
     *   Compute min and max scanline (in the y direction) for the given polygon
     */
    int min_scanline, max_scanline;
    min_max_scanline(first_point, &min_scanline, &max_scanline);


    /* Step 2
     *  Store all edges into an edge_table (ei_edge_t) in the increasing order of y and x.
     */
    ei_edge_t** edge_table = build_edge_table(first_point, min_scanline, max_scanline);

    // For debugging purpose
    print_edge_table(edge_table, min_scanline, max_scanline);


    ei_edge_t* active_edge_table = NULL;
    ei_edge_t* current_edge, *tmp_edge, *prev_edge;

    //loop over all scanlines
    for (int current_scanline = 0; current_scanline <= (max_scanline - min_scanline); current_scanline++) {

        /* Step 3
         *   Loop over all edges in the edge table at the current scanline
         *   Insert in active_edge_table all edges that cross this scanline,
         *   in an increasing order of x
         */
        current_edge = edge_table[current_scanline];
        prev_edge = active_edge_table;

        while (current_edge != NULL) {
            if (active_edge_table == NULL) {
                active_edge_table = current_edge;
                break;
            } else {
                if (active_edge_table->x_min > current_edge->x_min) {
                     /* TO BE COMPLETED */
                } else {
                     /* TO BE COMPLETED */
                }
            }
        }

        /* Step 4
         *  Remove from Active edge table, edges for wich y_max = current_scanline + min_scanline
         */

        /* TO BE COMPLETED */


        /* Step 5
         *  Fill the pixels that are inside the polygon (between two edges on the scanline) with alpha
         */
        current_edge = active_edge_table;
        ei_point_t pos;
        ei_color_t p;
        while (current_edge != NULL) {
            pos.y = current_scanline + min_scanline;
            /* TO BE COMPLETED */
        }


        /* Step 6
         *  Update the x_min coordinates of the edges in active table
         */
        current_edge = active_edge_table;
        tmp_edge = NULL;
        prev_edge = NULL;

        int i = 0;
        while (current_edge != NULL) {
            // update x_min (similar to Bresenham algorithm)

            /* TO BE COMPLETED */

            // Make sure active edge table remains sorted by increasing x
            if ((tmp_edge != NULL) && (tmp_edge->x_min > current_edge->x_min)) {
                // swap entries
                if (prev_edge != NULL) {
                    prev_edge->next = current_edge;
                    tmp_edge->next = current_edge->next;
                    current_edge->next = tmp_edge;
                } else {
                    active_edge_table = current_edge;
                    tmp_edge->next = current_edge->next;
                    current_edge->next = tmp_edge;
                }
                current_edge = tmp_edge;
            }
            prev_edge = tmp_edge;
            tmp_edge = current_edge;
            current_edge = current_edge->next;
            i++;
        }

    }

    //free memory

    /* TO BE COMPLETED */

    return 0;
}


/**
 * \brief   Compute min and max scanline (in the y direction) for the given polygon
 *
 * @param   first_point     The head of a linked list of the points of the polygon.
 * @param   min_scanline    Stores the minimum scanline
 * @param   max_scanline    Stores the maximum scanline
 */
void min_max_scanline_correction(const ei_linked_point_t* first_point, int* min_scanline, int* max_scanline)
{
    *min_scanline = first_point->point.y;
    *max_scanline = *min_scanline;
    const ei_linked_point_t* lpoint = first_point->next;

    while (lpoint != NULL) {
        if (lpoint->point.y < *min_scanline)
            *min_scanline = lpoint->point.y;
        if (lpoint->point.y > *max_scanline)
            *max_scanline = lpoint->point.y;
        lpoint = lpoint->next;
    }
}

/**
 * \brief   Allocate and store all edges of the polygon into an edge_table (ei_edge_t)
 *          in the increasing order of y and x.
 *          For example, edge_table[current_scanline] contains all edges for which
 *          lowest y position is current_scanline + min_scanline
 *
 * @param   first_point     The head of a linked list of the points of the polygon.
 * @param   min_scanline    The minimum scanline
 * @param   max_scanline    The maximum scanline
 */
ei_edge_t** build_edge_table_correction(const ei_linked_point_t* first_point, int min_scanline, int max_scanline)
{
    // Allocate and initialize edge table
    ei_edge_t** edge_table = (ei_edge_t**) malloc((max_scanline - min_scanline + 1) * sizeof(ei_edge_t*));
    for (int i = 0; i <= (max_scanline - min_scanline); i++)
        edge_table[i] = NULL;

    // Fill edge table
    ei_point_t start = first_point->point;
    const ei_linked_point_t* lpoint = first_point->next;
    ei_bool_t all_processed = EI_FALSE;
    int current_scanline;

    // Process polygon edges one by one
    while (!all_processed) {
        if (lpoint == NULL) {
            lpoint = first_point;
            all_processed = EI_TRUE;
        }

        ei_point_t end = lpoint->point;
        // skip horizontal edges
        if (start.y != end.y) {
            // Allocate current_edge and fill its fields: y_max, x_min, inv_m
            ei_edge_t* current_edge = (ei_edge_t*) malloc(sizeof(struct ei_edge_t));
            if (start.y < end.y) {
                current_edge->y_max = end.y;
                current_edge->x_min = start.x;
                current_edge->inv_m = (float)(end.x - start.x) / (float)(end.y - start.y);
                current_scanline = start.y - min_scanline;
            } else {
                current_edge->y_max = start.y;
                current_edge->x_min = end.x;
                current_edge->inv_m = (float)(start.x - end.x) / (float)(start.y - end.y);
                current_scanline = end.y - min_scanline;
            }

            // Insert current_edge in edge table sorted by increasing x of the lower end
            if (edge_table[current_scanline] == NULL) {
                // no prev_edge => insert curent_edge in edge_table[current_scanline]
                edge_table[current_scanline] = current_edge;
                current_edge->next = NULL;
            } else {
                // current_edge y_max superior => iterate over the list and find correct insertion position
                ei_edge_t* tmp_edge = edge_table[current_scanline];
                while (tmp_edge->next != NULL && (tmp_edge->next->y_max <= current_edge->y_max)) {
                    if ((tmp_edge->next->y_max == current_edge->y_max) && (tmp_edge->next->x_min > current_edge->x_min))
                        break;
                    tmp_edge = tmp_edge->next;
                }
                current_edge->next = tmp_edge->next;
                tmp_edge->next = current_edge;
            }
        }
        // Process next edge
        start = end;
        lpoint = lpoint->next;
    }

    return edge_table;
}

int ei_draw_polygon_correction(ei_surface_t surface, const ei_linked_point_t* first_point,
                               const ei_color_t color)
{
    if (first_point == NULL) {
        fprintf(stderr, "no point for the polygon\n");
        return 1;
    }

    /* Step 1
     *   Compute min and max scanline (in the y direction) for the given polygon
     */
    int min_scanline, max_scanline;
    min_max_scanline_correction(first_point, &min_scanline, &max_scanline);


    /* Step 2
     *  Store all edges into an edge_table (ei_edge_t) in the increasing order of y and x.
     */
    ei_edge_t** edge_table = build_edge_table_correction(first_point, min_scanline, max_scanline);

    // For debugging purpose
    // print_edge_table(edge_table, min_scanline, max_scanline);


    ei_edge_t* active_edge_table = NULL;
    ei_edge_t* current_edge, *tmp_edge, *prev_edge;

    //loop over all scanlines
    for (int current_scanline = 0; current_scanline <= (max_scanline - min_scanline); current_scanline++) {

        /* Step 3
         *   Loop over all edges in the edge table at the current scanline
         *   Insert in active_edge_table all edges that cross this scanline,
         *   in an increasing order of x
         */
        current_edge = edge_table[current_scanline];
        prev_edge = active_edge_table;

        while (current_edge != NULL) {
            if (active_edge_table == NULL) {
                active_edge_table = current_edge;
                break;
            } else {
                if (active_edge_table->x_min > current_edge->x_min) {
                    tmp_edge = current_edge->next;
                    current_edge->next = active_edge_table;
                    active_edge_table = current_edge;
                    current_edge = tmp_edge;
                } else {
                    while (prev_edge->next != NULL &&
                           prev_edge->next->x_min < current_edge->x_min) {
                        prev_edge = prev_edge->next;
                    }
                    tmp_edge = current_edge->next;
                    current_edge->next = prev_edge->next;
                    prev_edge->next = current_edge;
                    current_edge = tmp_edge;
                }
            }
        }

        /* Step 4
         *  Remove from Active edge table, edges for wich y_max = current_scanline + min_scanline
         */
        current_edge = active_edge_table;
        tmp_edge = NULL;
        while (current_edge != NULL) {
            if (current_edge->y_max == current_scanline + min_scanline) {
                if (tmp_edge == NULL)
                    active_edge_table = current_edge->next;
                else
                    tmp_edge->next = current_edge->next;
            } else {
                tmp_edge = current_edge;
            }
            current_edge = current_edge->next;
        }


        /* Step 5
         *  Fill the pixels that are inside the polygon (between two edges on the scanline) with alpha
         */
        current_edge = active_edge_table;
        ei_point_t pos;
        ei_color_t p;
        while (current_edge != NULL) {
            pos.y = current_scanline + min_scanline;
            for (pos.x = ceil(current_edge->x_min); pos.x <= floor(current_edge->next->x_min); pos.x++) {
                p = hw_get_pixel(surface, pos);
                hw_put_pixel(surface, pos, alpha_blend(color, p));
            }
            current_edge = current_edge->next->next;
        }


        /* Step 6
         *  Update the x_min coordinates of the edges in active table
         */
        current_edge = active_edge_table;
        tmp_edge = NULL;
        prev_edge = NULL;
        int i = 0;
        while (current_edge != NULL) {
            // update x_min (similar to Bresenham algorithm)
            current_edge->x_min = current_edge->x_min + current_edge->inv_m;

            // Make sure active edge table remains sorted by increasing x
            if ((tmp_edge != NULL) && (tmp_edge->x_min > current_edge->x_min)) {
                // swap entries
                if (prev_edge != NULL) {
                    prev_edge->next = current_edge;
                    tmp_edge->next = current_edge->next;
                    current_edge->next = tmp_edge;
                } else {
                    active_edge_table = current_edge;
                    tmp_edge->next = current_edge->next;
                    current_edge->next = tmp_edge;
                }
                current_edge = tmp_edge;
            }
            prev_edge = tmp_edge;
            tmp_edge = current_edge;
            current_edge = current_edge->next;
            i++;
        }
    }

    //free memory

    for (int current_scanline = 0; current_scanline <= (max_scanline - min_scanline); current_scanline++) {
        ei_edge_t* current_edge = edge_table[current_scanline];
        //loop over all edges crossing the current scanline
        while (current_edge != NULL) {
            tmp_edge = current_edge;
            current_edge = current_edge->next;
            if (tmp_edge == NULL)
                free(tmp_edge);
        }
    }
    free(edge_table);

    return 0;
}


void ei_draw_text(ei_surface_t surface, const ei_point_t* where,
                  const char* text, const ei_font_t font,
                  const ei_color_t* color)
{
    ei_size_t text_size;
    ei_surface_t s_text;
    ei_font_t default_font;
    
    if (font == NULL) {
        default_font = hw_text_font_create(ei_default_font_filename, ei_font_default_size);
        s_text = hw_text_create_surface(text, default_font, color);
        hw_text_font_free(default_font);
    } else {
        s_text = hw_text_create_surface(text, font, color);
    }
    
    
    hw_surface_lock(s_text);
    ei_copy_surface(surface, s_text, where, EI_TRUE);
    hw_surface_unlock(s_text);
    
    hw_surface_free(s_text);
}


void ei_fill(ei_surface_t surface, const ei_color_t* color, const ei_bool_t use_alpha)
{
    ei_point_t pos;
    ei_color_t c = color == NULL ? ei_font_default_color : *color;
    ei_color_t p;
    ei_size_t size = hw_surface_get_size(surface);
    for (pos.x = 0; pos.x < size.width; pos.x++) {
        for (pos.y = 0; pos.y < size.height; pos.y++) {
            if (use_alpha) {
                p = hw_get_pixel(surface, pos);
                hw_put_pixel(surface, pos, alpha_blend(c, p));
            } else {
                hw_put_pixel(surface, pos, c);
            }
        }
    }
}


void ei_copy_surface(ei_surface_t destination, const ei_surface_t source,
                     const ei_point_t* where, const ei_bool_t use_alpha)
{
    ei_point_t pos, new_pos;
    
    ei_size_t source_size = hw_surface_get_size(source);
    
    ei_size_t dst_size = hw_surface_get_size(destination);
    
    ei_color_t in_pixel, out_pixel;
    
    ei_point_t top_left = where == NULL ? (ei_point_t){0,0}:*where;
    
    for (pos.x = 0; pos.x < source_size.width; pos.x++) {
        for (pos.y = 0; pos.y < source_size.height; pos.y++) {
            in_pixel = hw_get_pixel(source, pos);
            
            new_pos.x = top_left.x + pos.x;
            new_pos.y = top_left.y + pos.y;
            
            if (new_pos.x>=0 && new_pos.x < dst_size.width
                && new_pos.y>=0 &&  new_pos.y < dst_size.height) {
                if (use_alpha) {
                    out_pixel = hw_get_pixel(destination, new_pos);
                    hw_put_pixel(destination, new_pos, alpha_blend(in_pixel, out_pixel));
                } else {
                    hw_put_pixel(destination, new_pos, in_pixel);
                }
            }
        }
    }
}
