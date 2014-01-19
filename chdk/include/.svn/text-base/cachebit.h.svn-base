#ifndef CACHEBIT_H
#define CACHEBIT_H

/*
Macros used to manipulate the uncached bit on addresses
may be used in core or module code

An uncached view of camera ram is available at a high address range
typically 0x10000000 or 0x40000000.
Sometimes it is desriable to convert from one to the other
NOTE the user is responsible for cleaning and/or flushing the caches
to ensure the data is coherent, if required.
These macro's only manipulate the bit on the address
*/

// get CAM_UNCACHED_BIT from camera_info, if camera.h define is not available (module code)
#ifndef CAM_UNCACHED_BIT
#define CAM_UNCACHED_BIT (camera_info.cam_uncached_bit)
#endif

// typeof is a gcc extension, used to ensure returned pointer is the same type
#define ADR_TO_UNCACHED(adr) ((typeof(adr))((unsigned)(adr)|CAM_UNCACHED_BIT))
#define ADR_TO_CACHED(adr) ((typeof(adr))((unsigned)(adr)&(~CAM_UNCACHED_BIT)))
#define ADR_IS_CACHED(adr) (!((unsigned)(adr)&(CAM_UNCACHED_BIT)))

#endif
