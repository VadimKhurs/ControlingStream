#include <node_api.h>
#include <Windows.h>
#include <iostream>
using namespace std;

int is_prime(int num)
{
    if (num <= 1)
        return 0;
    for (int i = 2; i <= num / 2; i++)
    {
        if (num % i == 0)
        {
        return 0;
        }
    }
    return 1; //if both failed then num is prime
}

int find_prime(int upper_limit, int ten)
{
  int largest_prime;
    cout << ten << endl;
  
  for (int i = 2; i <= upper_limit; i++)
  {
    if (is_prime(i))
    {
      largest_prime = i;
    }
  }
    

    INPUT input = {0};
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = VkKeyScanA('a');
    SendInput(1, &input, sizeof(input));
    ZeroMemory(&input, sizeof(input));
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(input));




    return largest_prime;
}

napi_value FindPrimes(napi_env env, napi_callback_info info){

    size_t argc = 2;
    napi_value args[2];
    int64_t upper_limit;
    int64_t ten;
    int64_t largest_prime;
    napi_value output;

    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    napi_get_value_int64(env, args[0], &upper_limit);
    napi_get_value_int64(env, args[1], &ten);

    largest_prime = find_prime(upper_limit, ten);

    napi_create_double(env, largest_prime, &output);
    return output;
}

napi_value init(napi_env env, napi_value exports)
{
    napi_value find_primes;

    napi_create_function(env, nullptr, 0, FindPrimes, nullptr, &find_primes);

    return find_primes;
}


NAPI_MODULE(NODE_GYP_MODULE_NAME, init);