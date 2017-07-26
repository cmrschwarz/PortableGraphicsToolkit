#ADDLIB $1/libSDL2main.a
#ADDLIB uuid
#ADDLIB imagehlp
#ADDLIB dinput8
#ADDLIB dxguid
#ADDLIB dxerr8
#ADDLIB user32
#ADDLIB gdi32
#ADDLIB winmm
#ADDLIB imm32
#ADDLIB ole32
#ADDLIB oleaut32
#ADDLIB shell32
#ADDLIB version
ar -M <<EOM
    CREATE $1/libpgt.a
    ADDLIB $1/libpgt_slim.a
    ADDLIB $1/libFreeImage.a
    ADDLIB $1/libfreetype$3.a
    ADDLIB $1/libfreetype-gl.a
    ADDLIB $1/libSDL2.dll.a
	ADDLIB $1/../lib/libglew32$3.a
	ADDLIB $2/libopengl32.a
	ADDLIB $2/libwsock32.a
    SAVE
    END
EOM
ranlib $1/libpgt.a
#$SHELL