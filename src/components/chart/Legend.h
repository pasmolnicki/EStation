#pragma once

#include <list>

// Essential includes for the UI elements
#include "../ScreenElement.h"
#include "../PosContainer.h"
#include "chart_data.h"

// For fast drawing of the text (i'm not using the TextElement for it's overheads)
#include "../../input/custom_buttons/TextButton.h"



namespace ui
{
  enum class LegendDirection{
    ROW,
    COLUMN
  };

  /*
  The legend should contain the following:
  - **the legend labels and it's colors**
  - position of the legend and it's max sizes (PosContainer)
  - label positioning (eigher in a row, column or in a grid (auto behavior))
  
  */
  class Legend: public ScreenElement, public PosContainer{

    /**
     * @brief Update the position of the element, total width and height, based on the direction and 
     *  whether we need to switch to the next row or column. The element's will try to fit into given
     *  window, otherwise they won't be rendered
     * @param x The x position of the element
     * @param y The y position of the element
     * @param total_width The total width of the elements
     * @param total_height The total height of the elements
     * @param element_width The width of the element
     * @param element_height The height of the element
     * @param newRowOrColumn Whether we need to switch to the next row or column
     */
    void _updatePosition(
      int& x, int& y, 
      int element_width, int element_height, 
      bool newRowOrColumn
    );

    /**
     * @brief Update the element's position
     * @param last_label The last label that was added
     * @param element_width The width of the element
     * @param element_height The height of the element
     * @param x The x position of the element
     * @param y The y position of the element
     */
    void _updateElement(
      TextButton* last_label, 
      int& element_width, int& element_height,
      int& x, int& y
    );

  public:
    typedef struct {
      TextButton label;
      uint16_t color;
    } LegendLabel;

    /**
     * @brief Construct a new Legend object, with the given position and maximum sizes
     * @param x The x position of the legend
     * @param y The y position of the legend
     * @param width The width of the legend
     * @param height The height of the legend
     * @param bg The background color of the legend
     * @param direction The direction of the legend lables
     * @note After creating the legend, you should add the labels and then call the prepareLayout function
     * to prepare the layout for drawing
     */
    Legend(
      int16_t x, int16_t y,
      uint16_t width, uint16_t height,
      uint16_t bg,
      LegendDirection direction
    );

    /**
     * @brief Prepare the legend for drawing
     * @note This function should be called after adding the labels, before drawing
     */
    void
    prepareLayout();

    /**
     * @brief Add a new label to the legend
     * @param label The label to add
     * @param color The color of the label
     */
    void
    addLabel(
      const String& label,
      uint16_t color
    );

    virtual void
    draw();

    /**
     * @brief This function will change the Legend's position to make it stick to the given position,
     * based on the Position enum (for example giving x,y and Position::TOP, will make the legend stick 
     * above given x,y position, essentially transforming it's coordinates to (y - legend_height, x))
     * @param x The x coordinate of the stick
     * @param y The y coordinate of the stick
     * @param pos The position of the stick
     * @note This function should be called after adding the labels and calling the `prepareLayout()` function
     */
    void 
    setStickPosition(
      int16_t x, int16_t y,
      Position pos
    );

    int _total_width, _total_height;
    uint16_t _bg;
    LegendDirection _direction;
    std::list<LegendLabel> _labels;
  };
}