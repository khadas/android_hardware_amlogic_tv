/*
 * Copyright 2022 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "android.hardware.tv.input-service"

#include <android-base/logging.h>
#include <android/binder_manager.h>
#include <android/binder_process.h>

#include "TvInput.h"

using ::aidl::android::hardware::tv::input::TvInput;

int main() {
    ABinderProcess_setThreadPoolMaxThreadCount(3);
    std::shared_ptr<TvInput> tvInput = ndk::SharedRefBase::make<TvInput>();
    tvInput->init();

    const std::string instance = std::string() + TvInput::descriptor + "/default";
    binder_status_t status =
            AServiceManager_addService(tvInput->asBinder().get(), instance.c_str());
    CHECK(status == STATUS_OK);
    LOG(INFO) << "TV INPUT HAL AIDL Service is started.";

    ABinderProcess_joinThreadPool();
    return EXIT_FAILURE;  // should not reached
}
