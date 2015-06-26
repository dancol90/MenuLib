#ifndef __lcd_drawer_h__
#define __lcd_drawer_h__

#include <MenuLib.h>
#include <LightLCD.h>

class LcdDrawer : public MenuItemDrawer {

	protected:
		LightLCD& lcd;

		uint8_t items_per_screen;
		
		
		uint8_t getNumLength(uint8_t num) {
			uint8_t numLength = 0, tmp;
			
			if(num == 0) return 1;
		
			// Init
			tmp = abs(num);
			
			while(tmp != 0) {
				tmp = tmp / 10;
				
				numLength++;
			}
			
			if(num < 0) numLength++;

			
			return numLength;
		}

		void setCenterCursor(uint8_t len, uint8_t y, uint8_t from = 0, uint8_t to = 0) {
			uint8_t x;

			if (to == 0)
				to = lcd.width();
			
			if( len > to - from ) 
				x = from;
			else
				x = from + ( to - from - len ) / 2;
			
			lcd.setCursor(x, y);
		}
		void drawCenterText(MenuItem* item, uint8_t y) {
			if (item->isTextFlash()) {
				const FlashString* text = reinterpret_cast<const FlashString*>(item->getText());

				setCenterCursor(lcd.getStringWidth(text), y);
				lcd.print(text);
			} else {
				const char* text = item->getText();

				setCenterCursor(lcd.getStringWidth(text), y);
				lcd.print(text);
			}
		}
		void drawCenterNumber(uint8_t num, uint8_t y,  uint8_t from = 0, uint8_t to = 0) {
			if (to == 0)
				to = lcd.width();
			
			// A digit has an average width of 4px
			setCenterCursor(4 * getNumLength(num), y, from, to);
			lcd.print(num);
		}
	 
		void drawMenu(Menu* menu) {
			uint8_t color = 1;
			uint8_t i = 0, y;
			char* secText;
			
			//lcd.drawLine(0, 7, lcd.width(), 7, 1) ;
			drawCenterText(menu, 0);
	
			ListEntry *e = menu->getCollection(), *first = e;
	
			if (!e) return;

			// Each screen contains 3 entry; when the third is reached, the next 3 will be shown

			// Find the right place where to start by scanning from the top.
			do {
				// Skip disabled items
				if (e->item->isEnabled()) {					
					if (i % items_per_screen == 0)
						first = e;

					i++;
				}
				
				if (e == menu->getSelectedListEntry())
					break;

				e = e->next;
			} while(e);


			e = first;
			i = 0;

			lcd.setCursor(0, 12);
			
			// Now actually draw the entries
			while (e && i < items_per_screen) {
				if (e->item->isEnabled()) {

					y = 9 + 13 * i;
					
					if(e == menu->getSelectedListEntry()) {
						lcd.fillRect(0, y, lcd.width(), 13, 1);
						lcd.setTextColor(0);
					} else
						lcd.setTextColor(1);

					secText = (char*)e->item->getSecondaryText();

					if(!secText)
						y += 3;
					else {
						// Draw secondary text
						lcd.setCursor(lcd.width() - lcd.getStringWidth(secText), y + 6);
						lcd.print(secText);
					}
					
					// Draw item's text
					lcd.setCursor(1, y);

					if (e->item->isTextFlash()) {
						const FlashString* text = reinterpret_cast<const FlashString*>(e->item->getText());
						lcd.print(text);
					} else {
						const char* text = e->item->getText();
						lcd.print(text);
					}

					i++;
				}

				e = e->next;
			}
			
			lcd.setTextColor(1);
		}

		#if defined PCD8544
		    #define RECT_W 68
		    #define RECT_H 14
		    #define RECT_Y 18
		#elif defined SSD1306
		    #define RECT_W 68
		    #define RECT_H 14
		    #define RECT_Y 18
		#endif

		#define RECT_X (lcd.width() - RECT_W) / 2
		#define TEXT_Y RECT_Y + (RECT_H - 7) / 2

		void drawSelector(NumericSelector* selector) {
			// Draw title
			drawCenterText(selector, 0);
			//lcd.drawLine(0, 8, lcd.width(), 8, 1) ;
			
			// Draw a rect around the value
			lcd.drawRect(RECT_X, RECT_Y, RECT_W, RECT_H, 1);
		 
			// Some decoration
			lcd.setCursor(RECT_X + 3, TEXT_Y);
			lcd.print('<');
			
			// Guess the x pos to center the value number
			drawCenterNumber(selector->getValue(), TEXT_Y);
			
			// Still some decorations
			lcd.setCursor(RECT_X + RECT_W - 6, TEXT_Y);
			lcd.println('>');
		}

		// Override this to extend functionalities
		void virtual drawOther(MenuItem* item) {};

	public:

		LcdDrawer(LightLCD& lcd, uint8_t num_items) : lcd(lcd), items_per_screen(num_items) {}

		void draw(MenuItem* item) {
			if(!item) return;
			
			lcd.clear();
			lcd.setCursor(0, 0);

			switch(item->getTypeId()) {
				case 'm':
					drawMenu((Menu*)item);
					break;

				// Actions and Check Boxes does not need to be drawn
				// case 'a':
				// case 'c':
				case 's':
					drawSelector((NumericSelector*)item);
					break;
				default:
					drawOther(item);
			}
			
			lcd.update();
		}
};

#endif
