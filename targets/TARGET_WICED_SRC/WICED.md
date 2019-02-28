1. Clone this to TARGET_WICED-folder to mbed-os.

This repo includes:
- Folder 43xxx_Wi-Fi from WICED-Studio version 6.1.0.85, extracted to WICED-folder.
- Patch file WM-BN-BM-22_SDK_5.1.x_platform_patch_v1.5 copied to WICED-folder.

1. Run refactor.sh script to patch SDK and delete unnecessary files.

1. Enable compilation of the WICED SDK and Mbed OS wrapper

To enable compilation of the WICED SDK, add the label `WICED` to the `target.extra_labels` and 'BLE' to the `target.features_add`
in your mbed_app.json:

``` json
{
    "target_overrides": {
        "MTB_ADV_WISE_1530": {
            "target.extra_labels_add": ["WICED"],
            "target.features_add": ["BLE"]
        },
        "MTB_MXCHIP_EMW3166": {
            "target.extra_labels_add": ["WICED"]
        },
    }
}
```