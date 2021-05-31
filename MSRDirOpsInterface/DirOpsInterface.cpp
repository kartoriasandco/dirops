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
    const DirOpsInterface* instanse() {
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

