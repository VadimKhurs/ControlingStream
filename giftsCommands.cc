#include <node_api.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <conio.h>
#include <random>

void clipBoardCopy(char* command){
    const size_t len = strlen(command) + 1;
    HGLOBAL hMem =  GlobalAlloc(GMEM_MOVEABLE, len);
    memcpy(GlobalLock(hMem),command, len);
    GlobalUnlock(hMem);
    OpenClipboard(0);
    EmptyClipboard();
    SetClipboardData(CF_TEXT, hMem);
    CloseClipboard();
}

int generateRand(int min, int max){
   static bool first = true;
   if (first) 
   {  
      srand( time(NULL) ); //seeding for the first time only!
      first = false;
   }
   return min + rand() % (( max + 1 ) - min);

}

/*
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
*/
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

void commandWrite(){
    WORD key = 0x1D;
    INPUT input;
    input.type = INPUT_KEYBOARD; 
    input.ki.wScan = key;
    
    input.ki.dwFlags = KEYEVENTF_SCANCODE;
    SendInput(1, &input, sizeof(INPUT));
    Sleep(10);
    clickButton(WORD(0x2F));    
    
    input.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));

}

void useCommand(char *command){
        clickButton(WORD(0x14));
        Sleep(8);
        clipBoardCopy(command);
        Sleep(23);
        commandWrite();
        clickButton(WORD(156));
}


void checkGift(std::string *gift){
    if(*gift == "Rosa"){    //ПОЛУЧИТЬ ЕДУ(3 Cтейка)
        useCommand("/give @a cooked_beef 3");
        return;
    }

    if(*gift == "Rosa"){    // 1 ЧАР ЯБЛОКО
        useCommand("/give @a enchanted_golden_apple 1");
        return;
    }

    if(*gift == "Rosa"){    //ВЫКЛЮЧИТЬ СОХРАНЕНИЕ ИНВЕНТАРЯ
        useCommand("/gamerule keepInventory false");
        return;
    }

    if(*gift == "Hello"){    //ИДТИ ВПЕРЁД
        char* str;
        
        sprintf(str, "/summon zombie ~%i ~2 ~%i {CustomName:'[{\"text\":\"Hello\", \"color\":\"green\", \"bold\":true}]',CustomNameVisible:1,Small:1,Invisible:1,Invulnerable:1,Riding:{id:\"FAFF\"}}", generateRand(-5, 5), generateRand(-5, 5));
        useCommand(str);
        return;
    }

    if(*gift == "Rosa"){    //ИДТИ ВПЕРЁД
        useCommand("/gamemode creative @a");
        return;
    }

    if(*gift == "Rosa"){    //ИДТИ ВПЕРЁД
        useCommand("/gamemode creative @a");
        return;
    }

    if(*gift == "Rosa"){    //ИДТИ ВПЕРЁД
        useCommand("/gamemode creative @a");
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
    
    std::string *gift = new std::string(buf); 

    
    checkGift(gift);

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