//#include <Adafruit_GFX.h>
//#include <Adafruit_PCD8544.h>

#include <LightPCD8544.h>

class NokiaLcdDrawer : public MenuItemDrawer {

	protected:
		LightPCD8544& lcd;
		
		
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

		void setCenterCursor(uint8_t len, uint8_t y, uint8_t from = 0, uint8_t to = LCD_WIDTH) {
			uint8_t x;
			
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
		void drawCenterNumber(uint8_t num, uint8_t y,  uint8_t from = 0, uint8_t to = LCD_WIDTH) {
			// A digit has an average width of 4px
			setCenterCursor(4 * getNumLength(num), y, from, to);
			lcd.print(num);
		}
	 
		void drawMenu(Menu* menu) {
			uint8_t color = 1;
			uint8_t i = 0, y;
			char* secText;
			
			//lcd.drawLine(0, 7, LCD_WIDTH, 7, 1) ;
			drawCenterText(menu, 0);
	
			ListEntry *e = menu->getCollection(), *first = e;
	
			if (!e) return;

			// Each screen contains 3 entry; when the third is reached, the next 3 will be shown

			// Find the right place where to start by scanning from the top.
			do {
				// Skip disabled items
				if (e->item->isEnabled()) {					
					if (i % 3 == 0)
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
			while (e && i < 3) {
				if (e->item->isEnabled()) {

					y = 9 + 13 * i;
					
					if(e == menu->getSelectedListEntry()) {
						lcd.fillRect(0, y, LCD_WIDTH, 13, 1);
						lcd.setTextColor(0);
					} else
						lcd.setTextColor(1);

					secText = (char*)e->item->getSecondaryText();

					if(!secText)
						y += 3;
					else {
						// Draw secondary text
						lcd.setCursor(LCD_WIDTH - lcd.getStringWidth(secText), y + 6);
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
		

		void drawSelector(NumericSelector* selector) {
			// Draw title
			drawCenterText(selector, 0);
			//lcd.drawLine(0, 8, LCD_WIDTH, 8, 1) ;
			
			// Draw a rect around the value
			lcd.drawRect(8, 18, 68, 14, 1) ;
		 
			// Some decoration
			lcd.setCursor(11, 21);
			lcd.print('<');
			
			// Guess the x pos to center the value number
			drawCenterNumber(selector->getValue(), 21);
			
			// Still some decorations
			lcd.setCursor(69, 21);
			lcd.println('>');
		}

		// Override this to extend functionalities
		void virtual drawOther(MenuItem* item) {};

	public:

		NokiaLcdDrawer(LightPCD8544& lcd) : lcd(lcd) {}
		
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

