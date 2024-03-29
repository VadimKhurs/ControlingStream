#include <node_api.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <conio.h>

void clipBoardCopy(char* command){
    const size_t len = strlen(command) + 1;
    HGLOBAL hMem =  GlobalAlloc(GMEM_MOVEABLE, len);
    memcpy(GlobalLock(hMem), command, len);
    GlobalUnlock(hMem);
    OpenClipboard(0);
    EmptyClipboard();
    SetClipboardData(CF_TEXT, hMem);
    CloseClipboard();
}

void cursor(){
    while(true){
        char g = getch();
        POINT xypos;
        if (g == 'a' || g == 'A')
		{
            GetCursorPos(&xypos);
			SetCursorPos(xypos.x + 10, xypos.y + 10);
		}

    }
}

void clickButton(WORD *key)
{
    INPUT *input = new INPUT;
    input->type = INPUT_KEYBOARD; 
    input->ki.wScan = *key;
    
    input->ki.dwFlags = KEYEVENTF_SCANCODE;
    SendInput(1, input, sizeof(INPUT));
    Sleep(3000); // hold key for x milliseconds
    
    input->ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
    SendInput(1, input, sizeof(INPUT));
    delete input;
}

void checkCommand(std::string *command){

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
    //WORD key = 0x4B;
    //clickButton(&key);
    
    //clipBoardCopy("asd");
    
    //cursor();

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