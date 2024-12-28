#pragma once
#include <stdint.h>
#include <bigstream.h>

typedef struct BigResource
{
    uint32_t extension, offset;

    uint16_t unknownValueA, unknownValueB;

    uint32_t fileSize;

    char* data;
} BigResource;

typedef struct Big
{
    uint32_t resourceCount;

    BigResource* resources;
} Big;

Big* big_from_stream(Stream* stream);
void big_delete(Big* big);

char* get_extension(BigResource resource);