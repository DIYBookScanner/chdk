    .globl blob_chdk_core, blob_chdk_core_size

    .section .blob_chdk_core
blob_chdk_core_start:
    .incbin CORE_FILE
blob_chdk_core_end:

    .text
blob_chdk_core_size:
    .long blob_chdk_core_end - blob_chdk_core_start
blob_chdk_core:
    .long blob_chdk_core_start
