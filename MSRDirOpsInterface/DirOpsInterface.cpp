#include "pch.h"

#include <Windows.h>
#include <objbase.h>
#include <string>

#include <jni.h>

#import "MSRDirOps.tlb" named_guids raw_interfaces_only

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
    double getFileSize(BSTR filePath) const {
        double ret;
        mi_->getFileSize(filePath, &ret);
        return ret;
    }

    double getDirectorySize(BSTR filePath) const {
        double ret;
        mi_->getDirectorySize(filePath, &ret);
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
    JNIEXPORT jlong JNICALL Java_dirops_DirectoryOperator_getFileSize(JNIEnv* env, jobject thisObj, jstring filePath) {
        const char* cstr = env->GetStringUTFChars(filePath, NULL);
        std::string bstrFilePath = std::string(cstr);
        return DirOpsInterface::instance()->getFileSize((BSTR)filePath);
    }

    JNIEXPORT jlong JNICALL Java_dirops_DirectoryOperator_getDirectorySize(JNIEnv* env, jobject thisObj, jstring filePath) {
        const char* cstr = env->GetStringUTFChars(filePath, NULL);
        std::string bstrFilePath = std::string(cstr);
        return DirOpsInterface::instance()->getDirectorySize((BSTR)filePath);
    }
}

