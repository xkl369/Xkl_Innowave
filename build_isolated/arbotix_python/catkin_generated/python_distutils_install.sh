#!/bin/sh

if [ -n "$DESTDIR" ] ; then
    case $DESTDIR in
        /*) # ok
            ;;
        *)
            /bin/echo "DESTDIR argument must be absolute... "
            /bin/echo "otherwise python's distutils will bork things."
            exit 1
    esac
fi

echo_and_run() { echo "+ $@" ; "$@" ; }

echo_and_run cd "/home/xkl/catkin_ws/src/arbotix_ros/arbotix_python"

# ensure that Python install destination exists
echo_and_run mkdir -p "$DESTDIR/home/xkl/catkin_ws/install_isolated/lib/python3/dist-packages"

# Note that PYTHONPATH is pulled from the environment to support installing
# into one location when some dependencies were installed in another
# location, #123.
echo_and_run /usr/bin/env \
    PYTHONPATH="/home/xkl/catkin_ws/install_isolated/lib/python3/dist-packages:/home/xkl/catkin_ws/build_isolated/arbotix_python/lib/python3/dist-packages:$PYTHONPATH" \
    CATKIN_BINARY_DIR="/home/xkl/catkin_ws/build_isolated/arbotix_python" \
    "/usr/bin/python3" \
    "/home/xkl/catkin_ws/src/arbotix_ros/arbotix_python/setup.py" \
    egg_info --egg-base /home/xkl/catkin_ws/build_isolated/arbotix_python \
    build --build-base "/home/xkl/catkin_ws/build_isolated/arbotix_python" \
    install \
    --root="${DESTDIR-/}" \
    --install-layout=deb --prefix="/home/xkl/catkin_ws/install_isolated" --install-scripts="/home/xkl/catkin_ws/install_isolated/bin"
