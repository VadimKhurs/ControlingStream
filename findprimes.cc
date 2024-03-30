#include <node_api.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <conio.h>

/*void cursor(){
    while(true){
        char g = getch();
        POINT xypos;
        if (g == 'd' || g == 'D')
		{
            GetCursorPos(&xypos);
			SetCursorPos(xypos.x + 72, xypos.y);
		}
        if (g == 'a' || g == 'A')
		{
            GetCursorPos(&xypos);
			SetCursorPos(xypos.x - 72, xypos.y);
		}
        if (g == 's' || g == 'S')
		{
            GetCursorPos(&xypos);
			SetCursorPos(xypos.x, xypos.y - 72);
		}
        if (g == 'w' || g == 'W')
		{
            GetCursorPos(&xypos);
			SetCursorPos(xypos.x, xypos.y + 72);
		}
        if (g == 'r' || g == 'R')
		{
			SetCursorPos(948, 542);
		}
        
        if (g == 'c' || g == 'C')
		{
            return;
		}

    }
}
*/

void holdButton(WORD key, int time){
    INPUT input;
    input.type = INPUT_KEYBOARD; 
    input.ki.wScan = key;
    
    input.ki.dwFlags = KEYEVENTF_SCANCODE;
    SendInput(1, &input, sizeof(INPUT));
    Sleep(time); // hold key for x milliseconds
    
    input.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));
}

void clickButton(WORD key)
{
    INPUT input;
    input.type = INPUT_KEYBOARD; 
    input.ki.wScan = key;
    
    input.ki.dwFlags = KEYEVENTF_SCANCODE;
    SendInput(1, &input, sizeof(INPUT));
    
    input.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));
}

void checkCommand(std::string *command){
    if(*command == "w"){    //ИДТИ ВПЕРЁД
        holdButton(WORD(0x11), 3000);
        return;
    }

    if(*command == "s"){    //ИДТИ НАЗАД
        holdButton(WORD(0x1F), 3000);
        return;
    }

    if(*command == "a"){    //ИДТИ ВЛЕВО
        holdButton(WORD(0x1E), 3000);
        return;
    }

    if(*command == "d"){    //ИДТИ ВПРАВО
        holdButton(WORD(0x20), 3000);
        return;
    }
    
    if(*command == "ctrl"){    // ВКЛ/ВЫКЛ присед
        clickButton(WORD(0x1D));
        return;
    }

    if(*command == "rc"){    //RIGHT CLICK 
        clickButton(WORD(0x25));
        return;
    }

    if(*command == "lc"){    //LEFT CLICK 
        clickButton(WORD(0x24));
        return;
    }

    if(*command == "r"){    //TURN RIGHT
        clickButton(WORD(0x4D));
        return;
    }

    if(*command == "l"){    //TURN LEFT
        clickButton(WORD(0x4B));
        return;
    }

    if(*command == "u"){    //TURN UP
        clickButton(WORD(0x48));
        return;
    }

    if(*command == "d"){    //TURN DOWN
        clickButton(WORD(0x50));
        return;
    }

    if(*command == "inventory"){    //Inventory
        clickButton(WORD(0x12));
        Sleep(80);
        SetCursorPos(948, 542);
        return;
    }

    if(*command == "break"){    //BREAK BLOCK
        holdButton(WORD(0x24), 3200);
        return;
    }

    if(*command == "spacePlace"){    //Place a block under a player
        holdButton(WORD(0x30),300);
        clickButton(WORD(0x25));
        return;
    }

    if(*command == "w1"){    //Walk forward 1 block
        holdButton(WORD(0x11),215);
        return;
    }

    if(*command == "run"){    //RUN
        clickButton(WORD(0x2A));
        holdButton(WORD(0x11),3000);
        clickButton(WORD(0x2A));
        return;
    }

    if(*command == "i up"){    //Inventory up
        POINT xypos;
        GetCursorPos(&xypos);
		SetCursorPos(xypos.x, xypos.y - 72);
        return;
    }

    if(*command == "i down"){    //Inventory down
        POINT xypos;
        GetCursorPos(&xypos);
		SetCursorPos(xypos.x, xypos.y + 72);
        return;
    }

    if(*command == "i left"){    //Inventory left
        POINT xypos;
        GetCursorPos(&xypos);
		SetCursorPos(xypos.x - 72, xypos.y);
        return;
    }

    if(*command == "i right"){    //Inventory right
        POINT xypos;
        GetCursorPos(&xypos);
		SetCursorPos(xypos.x + 72, xypos.y);
        return;
    }    
}

napi_value start(napi_env env, napi_callback_info info){
    size_t argc = 1;

    napi_value args[1];

    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    //get size of string
    size_t str_size;
    size_t str_size_read;
    napi_get_value_string_utf8(env, args[0], NULL, 0, &str_size);

    //get string
    char * buf;
    buf = (char*)calloc(str_size + 1, sizeof(char));
    str_size = str_size + 1;
    napi_get_value_string_utf8(env, args[0], buf, str_size, &str_size_read);
    
    std::string *command = new std::string(buf); 
    checkCommand(command);

    free(buf);
    return napi_value(0);
}

napi_value init(napi_env env, napi_value exports)
{
    napi_value resultCode;

    napi_create_function(env, nullptr, 0, start, nullptr, &resultCode);

    return resultCode;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, init);