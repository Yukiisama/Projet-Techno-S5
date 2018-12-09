#include "ei_draw.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include"ei_types.h"
#include <assert.h>
#define PI 3.14159265358979323846

ei_size_t t_size={0,0};
static inline ei_color_t alpha_blend(const ei_color_t in_pixel, const ei_color_t dst_pixel)
{
/* TO BE COMPLETED */
    double a = (double)in_pixel.alpha / 255;
    if(a>1 || a<0){
        fprintf(stderr,"Alpha must be in the interval [0,1]\n");
        exit(EXIT_FAILURE);
    }
    ei_color_t color;
    color.red=a*in_pixel.red + (1-a)*dst_pixel.red;
    color.green=a*in_pixel.green + (1-a)*dst_pixel.green;
    color.blue=a*in_pixel.blue + (1-a)*dst_pixel.blue;
    color.alpha=in_pixel.alpha+dst_pixel.alpha*(1-a);
    return color;
}

/*
Function draw_down_line is used to draw lines that is descreasing from left to right 
Ex : \
      \
       \
        \
This function is able to draw lines in 1st, 2nd, 5th and 6th octants.
The variable change = 1 when absolute value of (y1-y0) is greater than absolute value of (x1-x0)
*/
void draw_down_line(ei_surface_t surface, int x0, int x1, int y0, int y1, const ei_color_t color, int change)
{
    int x = x0;
    int y = y0;
    int dis_x = x1 - x0;
    int dis_y = y1 - y0;
    ei_point_t to_pos;

    int e = -(dis_x);
    while (x <= x1)
    {
        to_pos.x = x;
        to_pos.y = y;
        if (change == 1)
        { // case where x is actually y on the surface, same for y.
            to_pos.y = x;
            to_pos.x = y;
        }
        hw_put_pixel(surface, to_pos, color);
        x += 1;
        e += 2 * (dis_y);
        if (e >= 0)
        {
            y += 1;
            e -= 2 * (dis_x);
        }
    }
}

/*
Function draw_up_line is used to draw lines that is increasing from left to right 
Ex :    /
       / 
      / 
     /   
This function is able to draw lines in 3th, 4th, 7th and 8th octants.
The variable change = 1 when absolute value of (y1-y0) is greater than absolute value of (x1-x0)
*/
void draw_up_line(ei_surface_t surface, int x0, int x1, int y0, int y1, const ei_color_t color, int change)
{
    int x = x0;
    int y = y0;
    int dis_x = x1 - x0;
    int dis_y = y1 - y0;
    ei_point_t to_pos;
    int e = -(dis_x);
    int sign = 1;
    if (change == 1)
    {
        sign = -1; //case when x is actually y on the surface. Instead of increasing y, we descrease y.
    }
    while (x != x1)
    {
        to_pos.x = x;
        to_pos.y = y;
        if (change == 1)
        {
            to_pos.y = x;
            to_pos.x = y;
        }
        hw_put_pixel(surface, to_pos, color);
        x += sign;
        e += 2 * sign * (dis_y);
        if (e < 0)
        {
            y -= sign;
            e += 2 * sign * (dis_x);
        }
    }
}

void ei_draw_line(ei_surface_t surface, const ei_point_t start,
  const ei_point_t end, const ei_color_t color) {
    /* TO BE COMPLETED */
    //hw_surface_lock(surface);
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
    //hw_surface_unlock(surface);
    hw_surface_update_rects(surface);
  }




int ei_draw_polyline(ei_surface_t surface,
                     const ei_linked_point_t* first_point,
                     const ei_color_t color)
{
    ei_point_t start, end;
    //no point to draw  
    if (first_point == NULL)
        return 1;

    start = first_point->point;
    while (first_point->next != NULL)
    {
        end = first_point->next->point;
        ei_draw_line(surface, start, end, color);
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
    if (first_point == NULL)
    {
        fprintf(stderr, " no points for min_max_scanline\n;");
        return;
    }
    *min_scanline= first_point->point.y;
    *max_scanline= first_point->point.y;
    ei_linked_point_t *backup_point = (ei_linked_point_t *) first_point;
    while(backup_point->next!=NULL){
        if(backup_point->next->point.y> *max_scanline){
            *max_scanline= backup_point->next->point.y;
        }
        if(backup_point->next->point.y< *min_scanline){
            *min_scanline= backup_point->next->point.y;
        }
        backup_point=backup_point->next;
        //printf("min %d max %d\n",*min_scanline,*max_scanline);
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
 */
ei_edge_t** build_edge_table(const ei_linked_point_t* first_point, int min_scanline, int max_scanline)
{
    // Allocate the edge table and initialize all its entries to NULL
    ei_edge_t** edge_table;
    /* TO BE COMPLETED */
    const ei_linked_point_t* cp=first_point;
    int size=max_scanline-min_scanline ;
    //printf("size =%d\n",size);
    edge_table=(ei_edge_t **)malloc(size*sizeof(ei_edge_t *));
    assert(edge_table);
    for(int i =0; i<size;i++){edge_table[i]=NULL;}

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
        //printf("start x %d y %d , end x %d y %d \n",start.x,start.y,end.x,end.y);
        // skip horizontal edges
        if (start.y != end.y) {
            // Allocate current_edge and fill its fields: y_max, x_min, inv_m
            ei_edge_t* current_edge ;  /* TO BE COMPLETED */
            current_edge=(ei_edge_t *)malloc(sizeof(ei_edge_t));
            current_edge->next=NULL;
            //printf("start.y %d end.y %d\n",start.y,end.y);
            if (start.y < end.y) { //start.y is above end.y
                /* TO BE COMPLETED */
                current_edge->y_max=end.y;
                current_edge->x_min=(float)start.x;
                current_edge->inv_m=(float)(end.x-start.x)/(end.y-start.y); //inverse of m: 1/m
                current_scanline =  start.y-min_scanline ;
            } else {//end.y is above start.y
                 /* TO BE COMPLETED */
                current_edge->y_max=start.y;
                current_edge->x_min=(float)end.x;   
                current_edge->inv_m= (float) (start.x-end.x)/(start.y-end.y); //inverse of m: 1/m
                current_scanline =  end.y-min_scanline;
            }
            ei_edge_t* prev_edge = edge_table[current_scanline];

            ei_edge_t* g=prev_edge;
            ei_edge_t* b;
            //printf("prev_edge %d ,%f,%f \n",current_edge->y_max,current_edge->x_min,current_edge->inv_m);
            // Insert current_edge in edge table sorted by increasing x of the lower end
            if (prev_edge == NULL) {
                // no prev_edge => insert curent_edge in edge_table[current_scanline]
                 /* TO BE COMPLETED */
                 edge_table[current_scanline]=current_edge;
            } else {
                // current_edge x_min superior => iterate over the list and find correct insertion position
                /* TO BE COMPLETED */
                if(current_edge->x_min<prev_edge->x_min){
                    current_edge->next=prev_edge;
                    edge_table[current_scanline]=current_edge;
                }else{
                    while(g->next!=NULL && g->next->x_min<current_edge->x_min){
                        g=g->next;
                    }
                    b=g->next;
                    g->next=current_edge;
                    current_edge->next=b;
                    edge_table[current_scanline]=prev_edge;
                }
               
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
    //print_edge_table(edge_table, min_scanline, max_scanline);


    ei_edge_t* active_edge_table = NULL;
    ei_edge_t* current_edge, *tmp_edge, *prev_edge , *old;
    //loop over all scanlines
    for (int current_scanline = 0; current_scanline < (max_scanline - min_scanline); current_scanline++) {

        /* Step 3
         *   Loop over all edges in the edge table at the current scanline
         *   Insert in active_edge_table all edges that cross this scanline,
         *   in an increasing order of x
         */
        
        current_edge = edge_table[current_scanline];
        prev_edge = active_edge_table;
        old=NULL;
        //old=active_edge_table;
        while (current_edge != NULL) {
            printf("\n");
            print_edge_table_entry(current_edge);
            if (active_edge_table == NULL) {
                active_edge_table = current_edge;
                if (old != NULL)
                {
                    old->next = active_edge_table;
                }
                //prev_edge=active_edge_table;
                printf("scanline = %d here1\n",current_scanline);
                break;
            } else {
                if (active_edge_table->x_min > current_edge->x_min) {
                    /* TO BE COMPLETED */
                    tmp_edge = current_edge;
                    current_edge = current_edge->next;
                    tmp_edge->next = active_edge_table;
                    if(old!=NULL){
                        old->next=tmp_edge;
                        active_edge_table=old;
                    }else{
                        prev_edge = tmp_edge;
                    }
                    printf("scanline = %d here2\n", current_scanline);
                }
                else
                {
                    /* TO BE COMPLETED */
                    old=active_edge_table;
                    active_edge_table=active_edge_table->next;
                    printf("scanline = %d here3\n", current_scanline);
                    
                }
                
            }
            
        }
        if(prev_edge!=NULL){
            active_edge_table = prev_edge;
        }

        if (current_scanline == 0 || current_scanline == 60 || current_scanline == 130 || current_scanline == 280 
            || current_scanline == 380)
        {
            printf("key = %d \n", current_scanline + min_scanline);
            print_edge_table_entry(active_edge_table);
            
        }

        /* Step 4
         *  Remove from Active edge table, edges for wich y_max = current_scanline + min_scanline
         */

        /* TO BE COMPLETED */
        
        prev_edge=active_edge_table;
        tmp_edge=NULL;
        //If head edge's y_max is = current_scanline + min_scanline
        while (prev_edge!=NULL && prev_edge->y_max == current_scanline + min_scanline){
            prev_edge = prev_edge->next;
            
        }
        active_edge_table=prev_edge; // reposition pointer of active_edge_table
        while (prev_edge != NULL  )//loop until the end
        {
            //if it's not the end and there is no occurrence of current_scanline + min_scanline then loop pointer to next
            while (prev_edge != NULL  && prev_edge->y_max != current_scanline + min_scanline)
            {
                tmp_edge = prev_edge;
                prev_edge = prev_edge->next;
            }
            if (prev_edge==NULL){break;} //no edge with y_max = current_scanline +min_scanline
            tmp_edge->next=prev_edge->next;
            prev_edge=tmp_edge;
            active_edge_table=prev_edge;
        }
   

        if (current_scanline == 0 || current_scanline == 60 || current_scanline == 130 || current_scanline == 280 
            || current_scanline==380)
        {
         
            print_edge_table_entry(active_edge_table);
        }

        /* Step 5
         *  Fill the pixels that are inside the polygon (between two edges on the scanline) with alpha
         */
        current_edge = active_edge_table;
        ei_point_t pos,start,end;
        ei_color_t p;
        
        while (current_edge != NULL) {
            pos.y = current_scanline + min_scanline;
            start.y = pos.y;
            end.y = pos.y;
            /*TO BE COMPLETED */ 
            start.x=current_edge->x_min;
            end.x=current_edge->next->x_min;
            ei_draw_line(surface,start,end,color);
            current_edge=current_edge->next;
            current_edge=current_edge->next;
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
            current_edge->x_min=current_edge->x_min+current_edge->inv_m;
        
            // Make sure active edge table remains sorted by increasing x
            if ((tmp_edge != NULL) && (tmp_edge->x_min > current_edge->x_min))
            {
                // swap entries
                if (prev_edge != NULL)
                {
                    prev_edge->next = current_edge;
                    tmp_edge->next = current_edge->next;
                    current_edge->next = tmp_edge;
                }
                else
                {
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
    /*
    for (int current_scanline = 0; current_scanline < (max_scanline - min_scanline); current_scanline++)
    {
        if (edge_table[current_scanline] != NULL)
        {
            tmp_edge=NULL;
            current_edge = edge_table[current_scanline];
            while(current_edge!=NULL){
                tmp_edge=current_edge->next;
                free(current_edge);
                current_edge=tmp_edge;
            }
        }
    }
    free(edge_table);
    edge_table=NULL;
    */
    return 0;
}

ei_linked_point_t *arc(ei_point_t  centre, int radius, double start_angle , double end_angle){
  
    ei_linked_point_t *list=(ei_linked_point_t*)malloc(sizeof(ei_linked_point_t));
    //insert 1st point to the list 
    double radian = start_angle * PI/180; 
    list->point.x=centre.x+radius * cos(radian);
    list->point.y = centre.y + radius * sin(radian);
    list->next=NULL;
    ei_linked_point_t * backup =list;
    int sign=1;
    if(start_angle>end_angle){
        sign=-1;
    }
    while(start_angle!=end_angle){
        start_angle=start_angle+sign;
        radian = start_angle * PI / 180;
        ei_linked_point_t *new_point = (ei_linked_point_t *)malloc(sizeof(ei_linked_point_t));
        new_point->point.x = centre.x + radius * cos(radian);
        new_point->point.y = centre.y + radius * sin(radian);
        new_point->next=NULL;
        list->next=new_point;
        list=new_point;
    }
    return backup;

}


/**
 * \brief   Rounded the four corners of the rectangle.
 *
 * @param   rect     A rectangle defined by its top-left corner, and its size.
 * @param   radius   The radius use to find the center in the four corners
 * @param   part     0 : rounded the whole rectangle.
 *                   1 : rounded the uper part
 *                   2 : rounded the lower part
 */
ei_linked_point_t *rounded_frame(ei_rect_t *rect, int radius,int part)
{
    if (part != 0 && part != 1 && part != 2)
    {
        fprintf(stderr, "invalid parameter for part\n");
        return NULL;
    }
    if (radius <= 0)
    {
        fprintf(stderr, "radius invalid \n");
        exit(0);
    }
    assert(rect);
    int width = rect->size.width;
    int height = rect->size.height;
    ei_point_t top_left = rect->top_left;
    int h =height/2;
    ei_point_t center;
    ei_linked_point_t *liste_retourner_fin;
    ei_linked_point_t *list;
    ei_linked_point_t *first_point = (ei_linked_point_t *)malloc(sizeof(ei_linked_point_t));
    ei_linked_point_t *backup;
    ei_linked_point_t *h1 = (ei_linked_point_t *)malloc(sizeof(ei_linked_point_t));
    ei_linked_point_t *h2 = (ei_linked_point_t *)malloc(sizeof(ei_linked_point_t));
    h1->point.x=top_left.x+h; h1->point.y=top_left.y+h; h1->next=NULL;
    h2->point.x = top_left.x + width- h;
    h2->point.y = top_left.y + h;
    h2->next = NULL;

    switch (part){

        case 0 :{ // rounded the whole rectangle
            center.y = top_left.y + radius;
            center.x = top_left.x + radius;
            list = arc(center, radius, 180, 270);
            liste_retourner_fin = list;
            first_point->point = list->point;
            first_point->next = NULL;
            while (list->next != NULL)
            {
                list = list->next;
            }
            backup = list;
            //2nd arc
            
            center.x = top_left.x + width - radius;
            list = arc(center, radius, 270, 360);
            backup->next = list;
            while (list->next != NULL)
            {
                list = list->next;
            }
            backup = list;
            //3rd arc
            
            center.y = top_left.y + height - radius;
            list = arc(center, radius, 0, 90);
            backup->next = list;
            while (list->next != NULL)
            {
                list = list->next;
            }
            backup = list;
            //4th arc
            
            center.y = top_left.y + height - radius;
            center.x = top_left.x + radius;
            list = arc(center, radius, 90, 180);
            backup->next = list;
            while (list->next != NULL)
            {
                list = list->next;
            }
            list->next = first_point;
            break;
        }
        case 1 :{ //rounded the uper part of the rectangle
            center.y = top_left.y + radius;
            center.x = top_left.x + radius;
            list = arc(center, radius, 180, 270);
            liste_retourner_fin = list;
            first_point->point = list->point;
            first_point->next = NULL;
            while (list->next != NULL)
            {
                list = list->next;
            }
            backup = list;
            //2nd arc
            
            center.x = top_left.x + width - radius;
            list = arc(center, radius, 270, 315);
            backup->next = list;
            while (list->next != NULL)
            {
                list = list->next;
            }
            backup = list;
            //linked h2 then h1
            backup->next=h2;
            h2->next=h1;
            backup=h1;

            //4th arc
            center.y = top_left.y + height - radius;
            center.x = top_left.x + radius;
            list = arc(center, radius, 135, 180);
            backup->next = list;
            while (list->next != NULL)
            {
                list = list->next;
            }
            list->next = first_point;
            break;
        }
        case 2:{ //rounded the lower poart of rectangle
            //1er arc
            center.y = top_left.y + radius;
            center.x = top_left.x + width - radius;
            list = arc(center, radius, 315, 360);
            liste_retourner_fin = list;
            first_point->point = list->point;
            first_point->next = NULL;
            while (list->next != NULL)
            {
                list = list->next;
            }
            backup = list;
            //2nd arc

            center.y = top_left.y + height - radius;
            list = arc(center, radius, 0, 90);
            backup->next = list;
            while (list->next != NULL)
            {
                list = list->next;
            }
            backup = list;
            //3rd arc

            center.y = top_left.y + height - radius;
            center.x = top_left.x + radius;
            list = arc(center, radius, 90, 135);
            backup->next = list;
            while (list->next != NULL)
            {
                list = list->next;
            }
            list->next=h1;
            h1->next=h2;
            h2->next = first_point;
            break;
        }


        default : break;
    }
    
    return liste_retourner_fin;
}



void ei_draw_text(ei_surface_t surface, const ei_point_t *where,
                  const char *text, const ei_font_t font,
                  const ei_color_t *color)
{
    /* TO BE COMPLETED */
    if(surface==NULL || where==NULL || text==NULL || color==NULL){
        fprintf(stderr,"invalid arguments\n");
        exit(EXIT_FAILURE);
    }
    ei_surface_t text_surface;
    if(font==NULL){
        ei_font_t font_bis =hw_text_font_create(ei_default_font_filename,ei_font_default_size);
        text_surface = hw_text_create_surface(text,font_bis,&ei_font_default_color);
        hw_text_font_free(font_bis);
    }else{
        text_surface = hw_text_create_surface(text,font,color);
    }
    t_size =hw_surface_get_size(text_surface);
    hw_surface_lock(surface);
    ei_copy_surface(surface,text_surface,where,EI_TRUE);
    hw_surface_unlock(surface);
    hw_surface_free(text_surface);
}

void ei_fill(ei_surface_t surface, const ei_color_t *color, const ei_bool_t use_alpha)
{
    /* TO BE COMPLETED */
    if(surface==NULL){
        fprintf(stderr,"invalid surface\n");
        exit(EXIT_FAILURE);
    }
    if (color == NULL)
    {
        color = &ei_default_background_color; //use default background color.
    }
    ei_size_t win_size = hw_surface_get_size(surface);
    ei_point_t to_fill;
    ei_color_t org_color; //in case use_alpha is EI_TRUE then org_color store the details of origin pixel
    ei_color_t to_put;
    ei_color_t final_pixel = *color;
    to_fill.x = 0; //initiate coordinates x
    to_fill.y = 0; //initiate coordinates Y
    while (to_fill.y < win_size.height) //loop to put pixel to surface; ligne by ligne
    {
        while (to_fill.x < win_size.width)
        {
            if(use_alpha==EI_TRUE){
                org_color=hw_get_pixel(surface,to_fill);
                final_pixel=alpha_blend(*color,org_color);
            }
            hw_put_pixel(surface, to_fill, final_pixel);
            to_fill.x++;
        }
        to_fill.y++;
        to_fill.x = 0;
    }
}

void ei_copy_surface(ei_surface_t destination, const ei_surface_t source,
                     const ei_point_t *where, const ei_bool_t use_alpha)
{

    /* TO BE COMPLETED */
    /*Case where use_alpha is always EI_FALSE*/
    //quit if one of the surface is invalid
    if (destination == NULL || source == NULL)
    {
        fprintf(stderr, "invalid surface\n");
        exit(EXIT_FAILURE);
    }
    ei_point_t to_fill; //to_fill used to store the begining position in the destination surface

    if (where == NULL) //if where is NULL then to_fill is the top left corner (0,0)
    {
        to_fill.x = 0;
        to_fill.y = 0;
    }
    else
    { //to_fill get the asked position for destination surface
        to_fill.x = (*where).x;
        to_fill.y = (*where).y;
    }

    ei_size_t des_size = hw_surface_get_size(destination); //des_size stores destination's width and height
    ei_size_t src_size = hw_surface_get_size(source);      //src_size stores source's width and height
    ei_size_t final_size;                                  //position of width and height in destination to stop put pixels
    ei_color_t src_pixel;                                  //used to store pixel from src image
    ei_color_t dst_pixel;                                  //used to store pixel from dst image
    ei_color_t final_pixel;                                //final pixels after using alpha blending

    //initialize the default stop position : starting width +(add) src's width. Same for height.
    final_size.width = to_fill.x + src_size.width;
    final_size.height = to_fill.y + src_size.height;

    // if src's dimension is greater than destination's dimension then stop with is : destination width. Same for height.
    if (src_size.width > des_size.width - to_fill.x)
    {
        final_size.width = des_size.width;
    }
    if (src_size.height > des_size.height - to_fill.y)
    {
        final_size.height = des_size.height;
    }

    ei_point_t src_pos; //position used to get pixel from source image.
    src_pos.x = 0;
    src_pos.y = 0;
    int backup_to_fill = to_fill.x; //a backup of starting width in destination.

    while (to_fill.y < final_size.height) //copy pixels
    {
        while (to_fill.x < final_size.width)
        {
            src_pixel = hw_get_pixel(source, src_pos);
            if (use_alpha == EI_TRUE)
            {
                dst_pixel = hw_get_pixel(destination, to_fill);
                final_pixel = alpha_blend(src_pixel, dst_pixel);
            }else{
                final_pixel=src_pixel;
            }

            hw_put_pixel(destination, to_fill, final_pixel);

            src_pos.x++;
            to_fill.x++;
        }
        to_fill.y++;
        src_pos.y++;
        src_pos.x = 0;
        to_fill.x = backup_to_fill;
    }

}
