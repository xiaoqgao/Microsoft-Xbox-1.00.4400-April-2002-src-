cl -nologo -Ii386\ -I. -I\xbox\private\inc\aug01 -I\xbox\public\xdk\inc -I\xbox\private\ntos\inc -I\xbox\private\inc -I\xbox\private\inc -I\xbox\public\oak\inc -I\xbox\public\sdk\inc -I\xbox\public\sdk\inc\crt -D_X86_=1 -Di386=1  -DSTD_CALL -DCONDITION_HANDLING=1 -DNT_UP=1  -DNT_INST=0 -DWIN32=100 -D_NT1X_=100 -DWINNT=1 -D_WIN32_WINNT=0x0500 -DWINVER=0x0500 -D_WIN32_IE=0x0501 -D_XBOX -DXBOX=1 -DFASTPUSHER=1    -DWIN32_LEAN_AND_MEAN=1 -DDEVL=1 -DFPO=1    -DNDEBUG  /DSTARTUPANIMATION /DBINARY_RESOURCE /D_NTSYSTEM_ /DBOOTSOUND -DDEVKIT -DUNICODE -D_UNICODE      /c /Zel /Zp8 /Gy  /W3 /Gz  /QIfdiv- /QIf /QI0f /G6 /Gi- /Gm- /GX-  /GR- /GF -Z7 /Zvc6 /Oxs /Oy   -FI\xbox\public\sdk\inc\warning.h   ..\%1.cpp
move %1.obj obj\i386
