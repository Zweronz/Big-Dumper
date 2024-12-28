#include <big.h>

Big* big_from_stream(Stream* stream)
{
    Big* big = (Big*)malloc(sizeof(Big));

    stream_advance(stream, 20);

    big->resourceCount = stream_int(stream);

    stream_advance(stream, 40);
    big->resources = (BigResource*)calloc(big->resourceCount, sizeof(BigResource));

    for (uint32_t i = 0; i < big->resourceCount; i++)
    {
        big->resources[i].extension = stream_int(stream);
        big->resources[i].offset = stream_int(stream);
    }

    for (uint32_t i = 0; i < big->resourceCount; i++)
    {
        if (i == big->resourceCount - 1)
        {
            break;
            //idk
        }
        stream->pos = big->resources[i].offset;

        big->resources[i].unknownValueA = stream_short(stream);
        big->resources[i].unknownValueB = stream_short(stream);

        if (i == big->resourceCount - 1)
        {
            //big->resources[i].fileSize = stream->size - big->resources[i].offset - 4;
        }
        else
        {
            big->resources[i].fileSize = big->resources[i + 1].offset - big->resources[i].offset;
        }

        big->resources[i].data = (char*)stream_data(stream, big->resources[i].fileSize);
    }

    return big;
}

void big_delete(Big* big)
{
    for (uint32_t i = 0; i < big->resourceCount; i++)
    {
        free(big->resources[i].data);
    }

    free(big);
}

char* get_extension(BigResource resource)
{
    switch (resource.extension)
    {
        case 3071772280:
            if (resource.unknownValueB == 0)
            {
                return (char*)".png";
            }
            
            break;

        case 4253710164:
            if (resource.unknownValueB == 0)
            {
                return (char*)".wav";
            }

            break;
    }

    return (char*)"";
}