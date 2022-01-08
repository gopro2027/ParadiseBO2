/*
GOAL:
Dpad up/down to scroll
Dpad left/right
R1/L1 to swap between windows
R3 + Right Joystick to move current window
*/

//OnScreenKeyboard(0, title, presetMessage, len, KeyboardComplete, panelMode);


bool isButtonJustPressed(int button);
char ftosbuf[50];
char *FtoS(float fl) {
	snprintf(ftosbuf,sizeof(ftosbuf),"%f",fl);
	return ftosbuf;
}
float StoF(const char* s){
  float rez = 0, fact = 1;
  if (*s == '-'){
    s++;
    fact = -1;
  }
  for (int point_seen = 0; *s; s++){
    if (*s == '.'){
      point_seen = 1;
      continue;
    }
    int d = *s - '0';
    if (d >= 0 && d <= 9){
      if (point_seen) fact /= 10.0f;
      rez = rez * 10.0f + (float)d;
    }
  }
  return rez * fact;
}
//void drawText(char * text, int font, float x, float y, float scalex, float scaley, int r, int g, int b, int a, bool center);
void sleep(usecond_t time);
//struct Vector2 {float x,y;};//already declared in Vectors.h
struct Vector2i {int x,y;};
struct Color {int r,g,b,a;};
typedef Vector2 Ratio;
typedef Vector2i Pixel;
#define SCREENRES (*(Vector2i*)(0xF11A18/*0xF11A10 for the lower resolution*//*&Get_cgs()->refdef.width*/))
void RatioToPixel(Ratio ratio, Pixel *pixel) {
	pixel->x = (int)(ratio.x*(float)SCREENRES.x);
	pixel->y = (int)(ratio.y*(float)SCREENRES.y);
}
void PixelToRatio(Pixel pixel, Ratio *ratio) {
	ratio->x = (float)((float)pixel.x/SCREENRES.x);
	ratio->y = (float)((float)pixel.y/SCREENRES.y);
}
void drawRectByRatiosCentered(Ratio origin, Ratio size, Color color) {
	//printf("w: %i, h: %i\n",SCREENRES.x,SCREENRES.y);
	//printf("w1: %i, h1: %i\n\n",Get_cgs()->refdef.width,Get_cgs()->refdef.height);
	//GRAPHICS::DRAW_RECT(origin.x, origin.y, size.x, size.y,color.r,color.g,color.b,color.a);
	float width = size.x*SCREENRES.x;
	float height = size.y*SCREENRES.y;
	float x = origin.x*SCREENRES.x-(width/2);
	float y = origin.y*SCREENRES.y-(height/2);
	float c[] = {color.r/255.0f,color.g/255.0f,color.b/255.0f,color.a/255.0f};
	DrawShader(x,y,width,height,c,"white");
}
void drawRectByPixelsCentered(Pixel origin, Pixel size, Color color) {
	Ratio o,s;
	PixelToRatio(origin,&o);
	PixelToRatio(size,&s);
	drawRectByRatiosCentered(o,s,color);
}
/*void drawRectByPixels(Pixel origin, Pixel size, Color color) {//origin is top left, size extends right and down. size is NOT a second coordinate
	Pixel o;
	o.x = (float)origin.x+(float)size.x/2;
	o.y = (float)origin.y+(float)size.y/2;
	drawRectByPixelsCentered(o,size,color);
}*/
enum Alignment {
	Align_Left,
	Align_Center,
	Align_Right
};
void drawRectByPixels(Pixel origin, Pixel size, Color color, Alignment xalign = Align_Right, Alignment yalign = Align_Right) {//origin is top left, size extends right and down. size is NOT a second coordinate
	Pixel o;
	//o.x = (float)origin.x+(float)size.x/2;//align right x
	//o.x = (float)origin.x-(float)size.x/2;//align left x
	//o.x = (float)origin.x;//align center x

	//calculate the halves of size
	float xo2 = (float)size.x/2;
	float yo2 = (float)size.y/2;
	//assume center align was used cuz that requires like nothing and will be used in ever single one
	//Align_Center
	o.x = origin.x;
	o.y = origin.y;
	//check alignment left or right
	if (xalign == Align_Left)
		o.x -= xo2;//align left x
	else if (xalign == Align_Right)
		o.x += xo2;//align right x
	if (yalign == Align_Left)
		o.y -= yo2;//align left y
	else if (yalign == Align_Right)
		o.y += yo2;//align right y
	drawRectByPixelsCentered(o,size,color);
}
void drawTextByPixels(char * text, int font, Pixel origin, Ratio textsize, Color color, int addY = 0) {
	Ratio r;
	PixelToRatio(origin,&r);
	origin.y+=addY;//THIS IS NECESSARY BECAUSE THE COD ENGINE RENDERS TEXT A BIT DIFFERENT THAN THE GTA ENGINE AND IT MESSES UP THE Y VALUE FOR TEXT WHICH I CANNOT EASILY FIX WITHOUT SIMPLY ADDING THE NECESSARY BIT
	//drawText(text, font, r.x, r.y, textsize.x, textsize.y, color.r, color.g, color.b, color.a, false);
	float c[] = {color.r/255.0f,color.g/255.0f,color.b/255.0f,color.a/255.0f};
	DrawText(text,"fonts/720/normalfont",origin.x,origin.y,textsize.x/*0.9*//*0.74*/,c);
}
void nullfunc() {};
namespace SWindow {
	namespace WUtils {
		void* malloc(uint32_t a_uiSize) {
			static unsigned int addr = 0x10026000;//0x10060010;
			sys_addr_t l_uiAddr = addr;
			addr += a_uiSize;
			addr += 4-addr%4;
			//a_uiSize = ((a_uiSize + 65536) / 65536) * 65536;
			//sys_memory_allocate(a_uiSize, SYS_MEMORY_PAGE_SIZE_64K, &l_uiAddr);
			return (void*)l_uiAddr;
		}
		void free(void* a_Addr) {
			//sys_memory_free((sys_addr_t)a_Addr);
		}
		float getTextWidth(char * text, int font, Ratio scale) {
			//don't have a thing for this in cod
			return 400/SCREENRES.x;
		}
	};


	Color backgroundColor = {0,0,0,255};//0,0,0,70
	Color headerSelectedBackgroundColor = {52, 152, 219,255};//same
	Color headerTextColor = {52, 152, 219,255};//same
	Color optionColor = {255,255,255,255};
	Color headerColor = {0,0,0,255};
	Color selectorColor = {231, 76, 60,255};
	Color trueColor = {46, 204, 113,255};
	Color falseColor = {192, 57, 43,255};
	Pixel box10 = {10,10};//great little box
	Pixel box20 = {20,20};//bigger box. Unsure why
	int optionFont = 4;//2
	Ratio textSizeRatio = {0.7f,0.4f};//0.026 for font 2 and this size
	float optionFontDefaultYSize = 0.026;//for font 4
	int optionFontDefaultYSizePixels = 18;
	bool globalKeyboardBool = false;
	/*int selectionToRenderSlot(int selection) {
		return selection%maxOptionsPerPage;
	}
	int getMinOptionToRender(int selection) {
		int leftover = selection%maxOptionsPerPage;//2%10=2, 9%10=9,10%10=0,11%10=1,15%10=5
		int minOption = selection-leftover;//2-2=0,9-9=0,10-0=10,11-1=10,15-5=10
	}
	int getMaxOptionToRender(int selection) {
		//it will go from min to including (the return of this -1) so this is like maxOption
		int leftover = selection%maxOptionsPerPage;//2%10=2, 9%10=9,10%10=0,11%10=1,15%10=5
		int minOption = selection-leftover+maxOptionsPerPage;//2-2=0,9-9=0,10-0=10,11-1=10,15-5=10
	}*/
	enum OptionType {
		Option_None,//No special changeable value
		Option_Bool,
		Option_Int,
		Option_Float,
		Option_Hex,
		Option_String
	};

	union OptionValue {
		int i;
		unsigned int ui;
		float f;
		char *str;
		bool b;

		operator int () const { return i; }
		operator unsigned int () const { return ui; }
		operator float () const { return f; }
		operator char *() const { return str; }
		operator bool () const { return b; }
	};

	OptionValue nulloptionvalue;

	class WindowOption {
	public:
		char *optionText;
		char *optionInfo;
		OptionType optionType;
		OptionValue *optionValue;
		bool awaitingKeyboard;
		OptionValue minmax[2];
		bool useminmax;
		void (*callback)();
		Pixel size;
		
		void create() {
			callback = nullfunc;
			optionText = "Default Text";
			optionInfo = "Defualt Info";
			optionType = Option_None;
			Ratio r;
			r.y = optionFontDefaultYSize;
			r.x = 0.0;
			RatioToPixel(r,&size);
			useminmax = false;
		}
		void setup(char *text, void(*runOnSelect)() = nullfunc, OptionType type = Option_None, OptionValue *modifyValue = &nulloptionvalue, char *infotext = "") {
			optionText = text;
			optionInfo = infotext;
			callback = runOnSelect;
			optionType = type;
			optionValue = modifyValue;
		}
		void setHeightByRatio(float ratio) {
			Ratio r;
			PixelToRatio(size,&r);
			r.y = ratio;
			RatioToPixel(r,&size);
		}
		void setupMinMax(OptionValue min, OptionValue max) {
			minmax[0] = min;
			minmax[1] = max;
			useminmax = true;
		}
		void setupMinMax(int min, int max) {
			minmax[0].i = min;
			minmax[1].i = max;
			useminmax = true;
		}
		void setupMinMax(float min, float max) {
			minmax[0].f = min;
			minmax[1].f = max;
			useminmax = true;
		}
		void setCallback(void(*f)()) {
			callback = f;
		}
		void callCallback() {
			callback();
		}
		void fixMinMax() {
			if (useminmax) {
				if (optionType == Option_Int || optionType == Option_Hex) {
					if ((*optionValue).i > minmax[1].i)
						(*optionValue).i = minmax[0].i;
					if ((*optionValue).i < minmax[0].i)
						(*optionValue).i = minmax[1].i;
				}
				else if (optionType == Option_Float) {
					if ((*optionValue).f > minmax[1].f)
						(*optionValue).f = minmax[0].f;
					if ((*optionValue).f < minmax[0].f)
						(*optionValue).f = minmax[1].f;
				}
			}
		}
		void keyboardCallback(char *str/*int localClientNum, const wchar_t *text, int len*/) {
			/*void KeyboardComplete(int localClientNum, const wchar_t *text, int len) {
	char * CString = ToStr(text);
}
*/
			/*char str[KEYBOARD_MAX_LENGTH+1];
			for (int i = 0; i < len; i++) {
				str[i] = text[i];
			}
			str[len] = '\0';*/

			//awaitingKeyboard = false;
			if (optionType == Option_Int || optionType == Option_Hex) {
				//printf("String %s\n",str);
				(*optionValue).i = StoI(str);
			}
			else if (optionType == Option_Float) {
				(*optionValue).f = StoF(str);
			}
			else if (optionType == Option_String) {
				strcpy((*optionValue).str,str);
			}
			fixMinMax();
		}
		void increaseValue() {
			if (optionType == Option_Int || optionType == Option_Hex)
				(*optionValue).i++;
			if (optionType == Option_Float)
				(*optionValue).f++;
			fixMinMax();
		}
		void decreaseValue() {
			if (optionType == Option_Int || optionType == Option_Hex)
				(*optionValue).i--;
			if (optionType == Option_Float)
				(*optionValue).f--;
			fixMinMax();
		}
		/*void OnScreenKeyboard(int LocalClientNum, char *Title, char *PresetMessage, int Length, void(SWindow::WindowOption::*CompleteFunction)(int LocalClientNum, const wchar_t * wString, int Length), int PanelMode) {
			*(char*)0xD82144 = 1;
			opd_s AdNig = { 0x46710C, TOC };
			((void(*)(int, char *, char *, int, void(SWindow::WindowOption::*)(int, const wchar_t*, int), int))&AdNig)(LocalClientNum, Title, PresetMessage, Length, CompleteFunction, PanelMode);
		}*/
		void editValueWithKeyboard() {
			//TODO
			//GAMEPLAY::DISPLAY_ONSCREEN_KEYBOARD(0, "FMMC_KEY_TIP8", "", ""/*default text*/, "", "", "", 64);
			//globalKeyboardBool = true;
			//awaitingKeyboard = true;
			//KEYBOARD_MAX_LENGTH
			//OnScreenKeyboard(0, "Enter Value", "", KEYBOARD_MAX_LENGTH, &SWindow::WindowOption::keyboardCallback, 1);
			if (optionType == Option_Int || optionType == Option_Float || optionType == Option_Hex || optionType == Option_String)
				keyboardSWindow::openKeyboard(this);
		}
		OptionValue getOptionValue() {
			return *optionValue;
		}
		void updateSize(bool isSelected, bool isCurrentWindow) {
			Ratio r;
			//PixelToRatio(size,&r);
			r.y = optionFontDefaultYSize;
			//r.x = 0.0;
			r.x = WUtils::getTextWidth(optionText,optionFont,textSizeRatio);
			//printf("r.x: %s\n",FtoS(r.x));
			RatioToPixel(r,&size);//convert our sizes to pixels
			size.x+=5;//padding for the text
			//printf("size.y: %s\n",FtoS(size.y));
			if (optionType == Option_Bool)
				size.x+=10;//for the 10px bool box
			else if ((optionType == Option_Int || optionType == Option_Float || optionType == Option_Hex || optionType == Option_String) && isSelected && isCurrentWindow)
				size.y+=25;
		}
		
	};

	class Window {
	public:
		Pixel origin;
		char *header;
		WindowOption *options;
		int currentPage;
		int selectedOption;
		int maxOptions;
		bool isOpened;
		bool menuHasBeenFilledWithOptions;
		int maxOptionsPerPage;
#define SELECTION2RENDERSLOT(x) (x%maxOptionsPerPage)
#define MINOPTION2RENDER(x) (x-SELECTION2RENDERSLOT(x))
#define MAXOPTION2RENDER(x) (MINOPTION2RENDER(x)+maxOptionsPerPage)
		void create() {
			origin.x = 0;
			origin.y = 0;
			header = "Default";
			currentPage = 0;
			selectedOption = 0;
			isOpened = false;//change to false later so closed by default
			maxOptionsPerPage = 10;
		}
		void runStandard() {//this is constantly ran just like the render thread
			
		}
		void runSelected() {//this is ran while this menu is selected
			
		}
		void scrollDown() {
			selectedOption--;
			if (selectedOption < 0)
				selectedOption = maxOptions-1;
		}
		void scrollUp() {
			selectedOption++;
			if (selectedOption >= maxOptions)
				selectedOption = 0;
		}
		void render(bool isCurrentWindow) {//this is ran 100% of the time
			char *info = "";
			float currentY = origin.y;//start drawing option text at the start of the window origin
			Pixel size = {190,0};//100px minimum width
			Pixel sizeheader = {size.x,0};
			Ratio r = {0,optionFontDefaultYSize};
			RatioToPixel(r,&sizeheader);
			Pixel shiftedOrigin = {origin.x,origin.y+sizeheader.y};
			currentY+=sizeheader.y;//shift down so the header starts at origin and not the options
			//Pixel scrollerOrigin = {0,0};
			int minOptionToRender = MINOPTION2RENDER(selectedOption);
			int maxOptionToRender = MAXOPTION2RENDER(selectedOption);
			if (maxOptionToRender > maxOptions)
				maxOptionToRender = maxOptions;
			//printf("1\n");
			Pixel bgsize = {size.x,size.y};
			for (int i = minOptionToRender/*0*/; i < maxOptionToRender/*maxOptions*/; i++) {
				options[i].updateSize(i == selectedOption,isCurrentWindow);
				if (size.x<options[i].size.x) {
					size.x=options[i].size.x;
					bgsize.x=options[i].size.x;
				}
				bgsize.y+=options[i].size.y;
			}
			drawRectByPixels(shiftedOrigin,bgsize,backgroundColor);//100% correct main background
			for (int i = minOptionToRender/*0*/; i < maxOptionToRender/*maxOptions*/; i++) {
				size.y+=options[i].size.y;
				//printf("2\n");
				//cmd vsay hi
				//These pixel values spread from the very top of where the text was drawn to the top of the next text drawn. So if you have double the length, the center one for example would be the bottom off the current option
				Pixel o = {origin.x,currentY};//this is the point on the top left corner of the currently selected option
				Pixel om = {origin.x,currentY+(float)options[i].size.y/2.0f};//this is the point on the middle left of the currently selected option
				Pixel ob = {origin.x,currentY+options[i].size.y};//this is the point on the bottom left of the currently selected option
				Pixel orr = {origin.x+size.x,currentY};//this is the point on the top right corner of the currently selected option
				Pixel orm = {origin.x+size.x,currentY+(float)options[i].size.y/2.0f};//this is the point on the middle right of the currently selected option
				Pixel orb = {origin.x+size.x,currentY+options[i].size.y};//this is the point on the bottom right of the currently selected option
				
				if (i == selectedOption && isCurrentWindow) {//only display these if you are in the menu
					Pixel s = {size.x,options[i].size.y};
					drawRectByPixels(o,s,headerTextColor);//scrollbar to the left
				}
				
				drawTextByPixels(options[i].optionText,optionFont,o,textSizeRatio,optionColor,sizeheader.y);//100% correct
				//printf("3\n");
				if (i == selectedOption && isCurrentWindow) {//only display these if you are in the menu
					//scrollerOrigin.x = o.x;
					//scrollerOrigin.y = o.y;
					if (options[i].optionType == Option_Int) {
						char buf[12];
						//printf("3.1\n");
						snprintf(buf,sizeof(buf),"%i",options[i].getOptionValue().i);
						//printf("3.2\n");
						drawTextByPixels(buf,optionFont,om,textSizeRatio,optionColor,sizeheader.y);//om because it's twice as long so we want the middle
					}
					else if (options[i].optionType == Option_Hex) {
						char buf[12];
						//printf("3.3\n");
						snprintf(buf,sizeof(buf),"0x%X",options[i].getOptionValue().i);
						//printf("3.4\n");
						drawTextByPixels(buf,optionFont,om,textSizeRatio,optionColor,sizeheader.y);
					}
					else if (options[i].optionType == Option_Float) {
						//printf("3.5\n");
						drawTextByPixels(FtoS(options[i].getOptionValue().f),optionFont,om,textSizeRatio,optionColor,sizeheader.y);
						//printf("3.6\n");
					}
					else if (options[i].optionType == Option_String) {
						//printf("3.5\n");
						drawTextByPixels(options[i].getOptionValue().str,optionFont,om,textSizeRatio,optionColor,sizeheader.y);
						//printf("3.6\n");
					}
				}
				if (options[i].optionType == Option_Bool) {
					drawRectByPixels(orm,box10,options[i].getOptionValue().b?trueColor:falseColor,Align_Left,Align_Center);//box
				}
				currentY+=options[i].size.y;
			}
			
			//drawRectByPixels(shiftedOrigin,size,backgroundColor);//100% correct main background
			
			/*if (isCurrentWindow) {
				//draw scroller down here because drawing it under the background shader is bad
				Pixel s = {size.x,optionFontDefaultYSizePixels};
				drawRectByPixels(scrollerOrigin,s,headerTextColor);
			}*/
			sizeheader.x = size.x;
			drawRectByPixels(origin,sizeheader,isCurrentWindow?headerSelectedBackgroundColor:headerColor);//100% correct header background

			drawTextByPixels(header,optionFont,origin,textSizeRatio,isCurrentWindow?headerColor/*this is black*/:headerTextColor,sizeheader.y);//100% correct header text
		}
		void generateOptions(int optionCount) {
			//printf("4\n");
			menuHasBeenFilledWithOptions = true;
			options = (WindowOption*)WUtils::malloc(optionCount*sizeof(WindowOption));
			for (int i = 0; i < optionCount; i++) {
				options[i].create();
			}
			maxOptions = optionCount;
		}
		void setup(int optionCount, char *title,float x, float y) {
			generateOptions(optionCount);
			header = title;
			origin.x = x;
			origin.y = y;
		}
	};


	class WindowHandler {
	public:
		int windowCount;
		Window *windows;
		int selectedWindow;
		//int buttonPressTimeout;
		void create() {
			
		}
		void run() {
			//printf("5\n");
			//this snippet makes sure we are not on an unused window
			while (windows[selectedWindow].menuHasBeenFilledWithOptions == false || windows[selectedWindow].isOpened == false) {
				selectedWindow++;
				if (selectedWindow >= windowCount)
					selectedWindow = 0;
			}

			//printf("6\n");
			//if (buttonPressTimeout > 20) {//this shouldn't be much of a problem in my game cuz in this base it doesn't have a timeout to wait in between scripts
			if (isButtonJustPressed(B_L3)) {//BUTTON L3 WAS PRESSED
				//printf("\n\n\n\nX BUTTON PRESSED!!!\n\n\n\n");
				windows[selectedWindow].options[windows[selectedWindow].selectedOption].callCallback();//option was selected, run it
				//buttonPressTimeout = 0;
			}
			if (isButtonJustPressed(B_Square)) {//BUTTON SQUARE WAS PRESSED
				windows[selectedWindow].options[windows[selectedWindow].selectedOption].editValueWithKeyboard();//option was selected, run it
				//buttonPressTimeout = 0;
			}
			if (isButtonJustPressed(B_DpadLeft)) {//DPAD LEFT WAS PRESSED
				windows[selectedWindow].options[windows[selectedWindow].selectedOption].decreaseValue();//option was selected, run it
				//buttonPressTimeout = 0;
			}
			if (isButtonJustPressed(B_DpadRight)) {//DPAD RIGHT WAS PRESSED
				windows[selectedWindow].options[windows[selectedWindow].selectedOption].increaseValue();//option was selected, run it
				//buttonPressTimeout = 0;
			}
			if (isButtonJustPressed(B_DpadUp)) {//DPAD UP WAS PRESSED
				windows[selectedWindow].scrollDown();//scroll down
				//buttonPressTimeout = 0;
			}
			if (isButtonJustPressed(B_DpadDown)) {//DPAD DOWN WAS PRESSED
				windows[selectedWindow].scrollUp();//scroll up
				//buttonPressTimeout = 0;
			}
			if (isButtonJustPressed(B_R1)) {//R1 WAS PRESSED
				//buttonPressTimeout = 0;
				selectedWindow++;
				while (windows[selectedWindow].menuHasBeenFilledWithOptions == false || windows[selectedWindow].isOpened == false) {
					selectedWindow++;
					if (selectedWindow >= windowCount)
						selectedWindow = 0;
				}
			}
			if (isButtonJustPressed(B_L1)) {//L1 WAS PRESSED
				//buttonPressTimeout = 0;
				selectedWindow--;
				while (windows[selectedWindow].menuHasBeenFilledWithOptions == false || windows[selectedWindow].isOpened == false) {
					selectedWindow--;
					if (selectedWindow < 0)
						selectedWindow = windowCount-1;
				}
			}

			/*
			
			//keyboard manager
			if (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 1 && globalKeyboardBool == true) {
				//valid result
				globalKeyboardBool = false;
				char *result = GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT();
				for (int i = 0; i < windowCount; i++)
					if (windows[i].menuHasBeenFilledWithOptions)
						for (int j = 0; j < windows[i].maxOptions; j++)
							if (windows[i].options[j].awaitingKeyboard)
								windows[i].options[j].keyboardCallback(result);
			}
			else if (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 2 || GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 3) {
				//invalid
				for (int i = 0; i < windowCount; i++)
					if (windows[i].menuHasBeenFilledWithOptions)
						for (int j = 0; j < windows[i].maxOptions; j++)
							windows[i].options[j].awaitingKeyboard = false;
			}
			
			*/

				//printf("7\n");
			//}
			//buttonPressTimeout++;
			//printf("8\n");
			windows[selectedWindow].runSelected();
			//printf("9\n");
			for (int i = 0; i < windowCount; i++)
				if (windows[i].menuHasBeenFilledWithOptions)
					windows[i].runStandard();
			//printf("3.1\n");
			for (int i = 0; i < windowCount; i++)
				if (windows[i].menuHasBeenFilledWithOptions && windows[i].isOpened)
					windows[i].render(i==selectedWindow);
			//printf("10\n");
		}
		void createWindowPool(int windowCountt) {
			windowCount = windowCountt;
			windows = (Window*)WUtils::malloc(windowCount*sizeof(Window));
			for (int i = 0; i < windowCount; i++) {
				windows[i].create();
			}
		}
	};

	WindowHandler main;
};
using namespace SWindow;




namespace windowUtils {
	void closeAllWindows() {
		for (int i = 0; i < MENUS::Submenus_Count; i++)
			main.windows[i].isOpened = false;
	}
	void openWindow(int id) {
		Window *menu = &main.windows[MENUS::Main];
		menu->isOpened = true;
		menu = &main.windows[id];
		menu->isOpened = true;
	}
	void closeWindow(int id) {
		Window *menu = &main.windows[MENUS::Main];
		menu->isOpened = true;
		menu = &main.windows[id];
		menu->isOpened = false;
	}
	void setMenuOptionName(int windowid, int optionnumber, const char *text) {
		Window *menu = &main.windows[windowid];
		//printf("0x%X\n",(unsigned int)menu);
		menu->options[optionnumber].optionText = (char*)text;
	}
}





