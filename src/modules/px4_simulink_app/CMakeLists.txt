## This cmakelist.txt file was generated from
## the Embedded Coder Support Package for PX4 Autopilots

add_definitions(
-DMODEL=TestConnExample -DNUMST=1 -DNCSTATES=0 -DHAVESTDIO -DMODEL_HAS_DYNAMICALLY_LOADED_SFCNS=0 -DCLASSIC_INTERFACE=0 -DALLOCATIONFCN=0 -DTID01EQ=0 -DTERMFCN=1 -DONESTEPFCN=1 -DMAT_FILE=0 -DMULTI_INSTANCE_CODE=0 -DINTEGER_CODE=0 -DMT=0 -DPX4 -DFMUvx -DNULL=0 -DEXTMODE_DISABLETESTING -DEXTMODE_DISABLEPRINTF -DEXTMODE_DISABLE_ARGS_PROCESSING=1 -DDAEMON_MODE=1 -DSTACK_SIZE=64 -D__MW_TARGET_USE_HARDWARE_RESOURCES_H__ -DRT )


include_directories(
"/mnt/c/MATLAB/R2019a/extern/include"
"/mnt/c/MATLAB/R2019a/simulink/include"
"/mnt/c/MATLAB/R2019a/rtw/c/src"
"/mnt/c/MATLAB/R2019a/rtw/c/src/ext_mode/common"
"/mnt/c/MATLAB/R2019a/rtw/c/ert"
"/mnt/c/MATLAB/R2019a/rtw/c/src/ext_mode/serial"
"/mnt/c/ProgramData/MATLAB/SupportPackages/R2019a/toolbox/target/supportpackages/px4/include"
"/mnt/c/ProgramData/MATLAB/SupportPackages/R2019a/toolbox/target/supportpackages/px4/lib/Customize_Setup"
"/mnt/c/ProgramData/MATLAB/SupportPackages/R2019a/toolbox/target/shared/svd/include"
)

px4_add_module(
MODULE modules__px4_simulink_app
MAIN px4_simulink_app
STACK_MAIN 2000
SRCS
MW_SCI.c
MW_uORB_Read.cpp
ert_main.cpp
TestConnExample.cpp
TestConnExample_data.cpp
MW_PX4_TaskControl.cpp
nuttxinitialize.cpp
DEPENDS
platforms__common
)

string (REPLACE "-Werror" "" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
string (REPLACE "-Werror" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive -Wno-narrowing")

