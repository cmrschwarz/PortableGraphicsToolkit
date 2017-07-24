ar -M <<EOM
    CREATE $1/libpgt.a
    ADDLIB $1/libpgt_slim.a
    ADDLIB $1/libFreeImage.a
    ADDLIB $1/libfreetype$3.a
    ADDLIB $1/libfreetype-gl.a
    ADDLIB $1/libSDL2.a
	ADDLIB $1/libSDL2main.a
	ADDLIB $1/../lib/libglew32$3.a
	ADDLIB $2/libopengl32.a
    SAVE
    END
EOM
ranlib $1/libpgt.a
$SHELL