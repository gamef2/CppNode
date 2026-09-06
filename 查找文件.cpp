#include<iostream>
#include <Windows.h>
#include <string>
#include <assert.h>

typedef bool (*FindProc)(const char* chFinleName);

//遍历文件夹，chFolderPath为要遍历的文件夹路径。chFilter为遍历文件夹的过滤器，例如*.txt等
bool FindFolder(const char* chFolderPath, const char* chFilter, bool bFindFolder, FindProc pFindProc)
{
    assert(pFindProc);
    int nPathLen = strlen(chFolderPath) + MAX_PATH;
    char* pChPath = new char[nPathLen];
    sprintf(pChPath,  "%s\\%s", chFolderPath, chFilter);
    WIN32_FIND_DATA fileFindData;
    HANDLE hFind = ::FindFirstFile(pChPath, &fileFindData);            //找到第一个

    if (hFind == INVALID_HANDLE_VALUE)        //如果没有找到相关的文件信息，返回false
    {
        delete pChPath;
        return false;
    }

    //处理之后查找下一个，直到都找完
    do
    {
        if (fileFindData.cFileName[0] == '.')
        {
            continue;            //因为文件夹开始有"."和".."两个目录，要过滤掉
        }

        sprintf(pChPath, "%s\\%s", chFolderPath, fileFindData.cFileName);    //文件的完整路径

        //如果要查找递归查找文件夹
        if (bFindFolder && (fileFindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
        {
            FindFolder(pChPath, chFilter, bFindFolder, pFindProc);            //递归调用来查找他的子目录
        }

        //如果是文件
        pFindProc(pChPath);

    }while (::FindNextFile(hFind, &fileFindData));

    FindClose(hFind);                //关闭查找句柄
    delete pChPath;
    return true;
}

bool PrintFiles(const char* chFileName)
{
    std::cout<< chFileName<<std::endl;
    return true;
}
int main()
{
    FindFolder("D:", "*.*", true, &PrintFiles);
    getchar();
    MessageBox(NULL,TEXT("good"),NULL,TEXT("haha"));
    return 0;
}
