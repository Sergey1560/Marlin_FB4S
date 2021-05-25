#
# buildroot/share/PlatformIO/scripts/mks_robin_nano35.py
#
Import("env")
import marlin
marlin.prepare_robin("0x08007000", "mks_robin_nano.ld", "Robin_nano35.bin")

env.Replace(
    UPLOADER="curl",
    UPLOADCMD="$UPLOADER -v -H 'Content-Type:application/octet-stream' http://$UPLOADERFLAGS/upload?X-Filename=Robin_Nano35.bin --data-binary @$BUILD_DIR/Robin_nano35.bin"
)