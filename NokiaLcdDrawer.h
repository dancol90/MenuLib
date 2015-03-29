//#include <Adafruit_GFX.h>
//#include <Adafruit_PCD8544.h>

#include <LightPCD8544.h>

class NokiaLcdDrawer : public MenuItemDrawer {

	protected:
		LightPCD8544& lcd;
		
		
		int getNumLength(int num) {
			int numLength = 0, tmp;
			
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

		void setCenterCursor(int len, int y, int from = 0, int to = LCD_WIDTH) {
			int x;
			
			if( len > to - from ) 
				x = to;
			else
				x = ( to - from - len ) / 2;
			
			lcd.setCursor(x, y);
		}
		void drawCenterText(MenuItem* item, int y) {
			if (item->isTextFlash()) {
				const __FlashStringHelper* text = reinterpret_cast<const __FlashStringHelper*>(item->getText());

				setCenterCursor(lcd.getStringWidth(text), y);
				lcd.print(text);
			} else {
				const char* text = item->getText();

				setCenterCursor(lcd.getStringWidth(text), y);
				lcd.print(text);
			}
		}
		void drawCenterNumber(int num, int y,  int from = 0, int to = LCD_WIDTH) {
			// A digit has an average width of 4px
			setCenterCursor(4 * getNumLength(num), y, from, to);
			lcd.print(num);
		}
	 
		void drawMenu(Menu* menu) {
			uint8_t color = 1;
			
			//lcd.drawLine(0, 7, LCD_WIDTH, 7, 1) ;
			drawCenterText(menu, 0);
	
			ListEntry* e = menu->getCollection();
	
			if (!e) return;

			// 4 righe per schermata

			int currIndex = 0, before, y;
			//char lineText[21];
			char* secText;

			while(e->item != menu->getSelectedItem()) {
				currIndex++;
				
				e = e->next;
				
				// Controllo per sicurezza
				if(!e) break;
			}
			
			before = currIndex % 3;

			for(int i = 0; i < before; i++)
				e = e->prev;

			lcd.setCursor(0, 12);
			
			for(int i = 0; i < 3 && e; i++) {
				y = 9 + 13 * i;
				
				if(i == before) {
					lcd.fillRect(0, y, LCD_WIDTH, 13, 1);
					lcd.setTextColor(0);
				} else
					lcd.setTextColor(1);

				//text    = e->item->getText();
				secText = (char*)e->item->getSecondaryText();
				
				// If the string is longer than the screen, truncate it and leave three chars for the dots
				// (e.g.: "this is longer than the screen" => "this is longer th...")
				/*if(lcd.getStringWidth(text) > LCD_WIDTH) {
					strncpy(lineText, text, 16);
					
					lineText[16] = 0;
					
					strcat(lineText, "...");
					
					text = lineText;
				}*/
				
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
					const __FlashStringHelper* text = reinterpret_cast<const __FlashStringHelper*>(e->item->getText());
					lcd.print(text);
				} else {
					const char* text = e->item->getText();
					lcd.print(text);
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

