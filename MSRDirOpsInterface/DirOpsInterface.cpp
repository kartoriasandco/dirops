#include "pch.h"

#include <Windows.h>
#include <objbase.h>
#include <string>
#include <locale>
#include <codecvt>

#include <jni.h>

#import "C:\dev\dirops\MSRDirOps\bin\x64\Debug\msrdirops.tlb" named_guids raw_interfaces_only

using namespace MSRDirOps;

class DirOpsInterface
{
	DirOpsInterface(const DirOpsInterface&) = delete;
	DirOpsInterface& operator=(const DirOpsInterface&) = delete;

private:
    DirOpsInterface() noexcept
    {
        mi_.CreateInstance(CLSID_DirOps);
    }
public:
    const static DirOpsInterface* instance() {
        if (!_co_init) {
            ::CoInitialize(NULL);
            _co_init = true;
        }
        static DirOpsInterface _ret;
        return &_ret;
    }

    __int64 getFileSize(std::string filePath) const {
        __int64 ret;
        char* charArray;
        std::string str_obj(filePath);
        charArray = &str_obj[0];
        mi_->getFileSize(charArray, &ret);
        return ret;
    }

    __int64 getDirectorySize(std::string filePath) const {
        __int64 ret;
        char* charArray;
        std::string str_obj(filePath);
        charArray = &str_obj[0];
        mi_->getDirectorySize(charArray, &ret);
        return ret;
    }

    ~DirOpsInterface() noexcept
    {
        ::CoUninitialize();
    }
private:
    IDirOpsPtr mi_;
    static bool _co_init;
};

bool DirOpsInterface::_co_init = false;

extern "C" {

    JNIEXPORT jlong JNICALL Java_dirops_DirectoryOperator_vbrGetFileSize(JNIEnv* env, jobject thisObj, jstring filePath) {
        const char* cstr = env->GetStringUTFChars(filePath, NULL);
        std::string bstrFilePath = std::string(cstr);
        return DirOpsInterface::instance()->getFileSize(bstrFilePath);
    }

    JNIEXPORT jlong JNICALL Java_dirops_DirectoryOperator_vbrGetDirectorySize(JNIEnv* env, jobject thisObj, jstring filePath) {
        const char* cstr = env->GetStringUTFChars(filePath, NULL);
        std::string bstrFilePath = std::string(cstr);
        return DirOpsInterface::instance()->getDirectorySize(bstrFilePath);
    }
}

