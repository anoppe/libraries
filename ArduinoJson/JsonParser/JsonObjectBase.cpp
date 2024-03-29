/*
* Arduino JSON library
* Benoit Blanchon 2014 - MIT License
*/

#include <stdlib.h> // for strtol, strtod
#include "JsonObjectBase.h"

using namespace ArduinoJson::Parser;

int JsonObjectBase::getNestedTokenCount(jsmntok_t* token)
{
    int tokensToVisit = token->size;
    int count = 0;

    while (tokensToVisit)
    {
        count++;
        token++;
        tokensToVisit--;
        tokensToVisit += token->size;
    }

    return count;
}

bool JsonObjectBase::getBoolFromToken(jsmntok_t* token)
{
    if (token == 0 || token->type != JSMN_PRIMITIVE) return 0;

    // "true"
    if (json[token->start] == 't') return true;

    // "false"
    if (json[token->start] == 'f') return false;

    // "null"
    if (json[token->start] == 'n') return false;
    
    // number
    return strtol(json + token->start, 0, 0) != 0;
}

double JsonObjectBase::getDoubleFromToken(jsmntok_t* token)
{
    if (token == 0 || token->type != JSMN_PRIMITIVE) return 0;

    return strtod(json + token->start, 0);
}

long JsonObjectBase::getLongFromToken(jsmntok_t* token)
{
    if (token == 0 || token->type != JSMN_PRIMITIVE) return 0;

    return strtol(json + token->start, 0, 0);
}

char* JsonObjectBase::getStringFromToken(jsmntok_t* token)
{
    if (token == 0 || token->type != JSMN_PRIMITIVE && token->type != JSMN_STRING)
        return 0;

    // add null terminator to the string
    json[token->end] = 0;

    return json + token->start;
}