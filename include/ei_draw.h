/**
 *  @file ei_draw.h
 *  @brief  Graphical primitives to draw lines, polygons, text, and
 *operation of drawing
 *    surfaces.
 *
 *  \author
 *  Created by François Bérard on 30.12.11.
 *  Copyright 2011 Ensimag. All rights reserved.
 *
 */

#ifndef EI_DRAW_H
#define EI_DRAW_H

#include <stdint.h>
#include "ei_types.h"
#include "hw_interface.h"

#ifdef __cplusplus
extern "C"{
#endif 

    /**
     * \brief Draws a filled polygon.
     *
     * @param surface     Where to draw the polygon. The surface must be locked* by \ref hw_surface_lock.
     * @param first_point The head of a linked list of the points of the polygon.
     *                    It is either NULL (i.e. draws nothing), or has more than 2 points.
     * @param color       The color used to draw the polygon, alpha channel is managed.
     * @return  Returns 0 on success, 1 on failure (no point for the polygon).
     */
    int ei_draw_polygon(ei_surface_t surface, const ei_linked_point_t* first_point,
                        const ei_color_t color);
    int ei_draw_polygon_correction(ei_surface_t surface, const ei_linked_point_t* first_point,
                        const ei_color_t color);

    /**
     * \brief Draws a single line using Bresenham algorithm
     *
     * @param surface Where to draw the line. The surface must be *locked* by \ref hw_surface_lock.
     * @param start   Start position of the line.
     * @param end     End position of the line.
     * @param color   The color used to draw the line, alpha channel is managed.
     */
    void ei_draw_line(ei_surface_t surface, const ei_point_t start,
                      const ei_point_t end, const ei_color_t color);
    void ei_draw_line_correction(ei_surface_t surface, const ei_point_t start,
                      const ei_point_t end, const ei_color_t color);


    /**
     * \brief Draws a line made of many line segments.
     *
     * @param surface     Where to draw the line. The surface must be *locked* by \ref hw_surface_lock.
     * @param first_point The head of a linked list of the points of the line. It can be NULL (i.e. draws nothing),
     *                    can have a single point, or more. If the last point is the same as the first point,
     *                    then this pixel is drawn only once.
     * @param color       The color used to draw the line, alpha channel is managed.
     * @return  Returns 0 on success, 1 on failure (no point in the polyline).
     */
    int ei_draw_polyline(ei_surface_t surface,
                     const ei_linked_point_t* first_point,
                     const ei_color_t color);
    int ei_draw_polyline_correction(ei_surface_t surface,
                     const ei_linked_point_t* first_point,
                     const ei_color_t color);


    /**
     * \brief Draws text by calling \ref hw_text_create_surface.
     *
     * @param surface   The surface where to draw the text. The surface must be *locked* by \ref hw_surface_lock.
     * @param where     Coordinates, in the surface, where to anchor the *top-left corner of the rendered text.
     * @param text      The string of the text. Can't be NULL.
     * @param font      The font used to render the text. If NULL, the \ref ei_default_font is used.
     * @param color     The text color. Can't be NULL. The alpha parameter is not used.
     */
    void ei_draw_text(ei_surface_t surface, const ei_point_t* where,
                 const char* text, const ei_font_t font,
                 const ei_color_t* color);

    /**
     * \brief Fills the surface with the specified color.
     *
     * @param surface   The surface to be filled. The surface must be *locked* by \ref hw_surface_lock.
     * @param color     The color used to fill the surface.
     *                  If NULL, it means that the caller want it painted black (opaque, \ref ei_font_default_color).
     * @param use_alpha   If true, the final pixels are a combination of source and destination pixels
     *                    weighted by the source alpha channel. The transparency of the final pixels is set to opaque.
     *                    If false, the final pixels are an exact copy of the source pixels, including the alpha channel.
     
     */
    void ei_fill(ei_surface_t surface, const ei_color_t* color, const ei_bool_t use_alpha);

    /**
     * \brief Copies a surface source onto another one destination.
     *        Both the source and destination surfaces must be *locked* by \ref hw_surface_lock.
     *
     * @param destination The surface on which to copy pixels from the source surface.
     * @param source      The surface from which to copy pixels.
     * @param where    Coordinates, in the destination surface, where to anchor the *top-left corner of the  source
     *                    surface. If NULL, the entire source surface is used.
     *                    If not NULL, defines the rectangle on the source surface from which to copy the pixels.
     * @param use_alpha   If true, the final pixels are a combination of source and destination pixels
     *                    weighted by the source alpha channel. The transparency of the final pixels is set to opaque.
     *                    If false, the final pixels are an exact copy of the source pixels, including the alpha channel.
     *
     */

    void ei_copy_surface(ei_surface_t destination, const ei_surface_t source,
                         const ei_point_t *where, const ei_bool_t use_alpha);


#ifdef __cplusplus
}
#endif 

#endif
