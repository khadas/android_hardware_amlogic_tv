package  tv_input_hal

import (
    "fmt"
    "android/soong/android"
    "android/soong/cc"
)

func init() {
    android.RegisterModuleType("hardware_tv_hal_go_defaults", tv_input_hal_DefaultsFactory)
}

func tv_input_hal_DefaultsFactory() (android.Module) {
    module := cc.DefaultsFactory()
    android.AddLoadHook(module, func(ctx android.LoadHookContext) {
        type props struct {
            Cflags []string
            Shared_libs []string
            Static_libs []string
        }
        p := &props{}

        vconfig := ctx.Config().VendorConfig("amlogic_vendorconfig")
        if vconfig.Bool("support_dtvkit") == true {
            fmt.Println("tv_input support_dtvkit")
            p.Cflags = append(p.Cflags, "-DSUPPORT_DTVKIT")
            p.Shared_libs = append(p.Shared_libs, "libdtvkithidlclient")
            p.Shared_libs = append(p.Shared_libs, "vendor.amlogic.hardware.dtvkitserver@1.0")
            p.Static_libs = append(p.Static_libs, "libjsoncpp")
        } else {
            fmt.Println("tv_input no support_dtvkit")
        }
        ctx.AppendProperties(p)
    })

    return module
}
