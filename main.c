#include <big.h>
#include <string.h>
#include <direct.h>

int main(int argc, char** argv)
{
    Stream* stream = stream_create(argv[1]);
    Big* big = big_from_stream(stream);

    char directory[256];
    sprintf(directory, "output/%s", argv[1]);

    _mkdir("output");
    _mkdir(directory);

    stream_close(stream);

    for (uint32_t i = 0; i < big->resourceCount; i++)
    {
        char fileName[256];

        sprintf(fileName, "%s/file_%03i_%04x%s", directory, i, big->resources[i].extension, get_extension(big->resources[i]));

        FILE* file = fopen(fileName, "wb");
        fwrite((void*)big->resources[i].data, 1, big->resources[i].fileSize, file);

        fclose(file);
    }

    big_delete(big);

    return 0;
}