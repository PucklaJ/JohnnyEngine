# Absolute path to this script, e.g. /home/user/bin/foo.sh
SCRIPT=$(readlink -f "$0")
# Absolute path this script is in, thus /home/user/bin
SCRIPTPATH=$(dirname "$SCRIPT")

echo Writing all needed environment variables into .profile ...

sed -i '$ a\\n' $HOME/.profile
sed -i "$ a\export JOHNNY_ROOT=$SCRIPTPATH" $HOME/.profile
sed -i '$ a\export JOHNNY_INCLUDE=$JOHNNY_ROOT/include' $HOME/.profile
sed -i '$ a\export JOHNNY_LIB=$JOHNNY_ROOT/projects/Ubuntu/Release' $HOME/.profile
sed -i '$ a\export JOHNNY_LIB_DBG=$JOHNNY_ROOT/projects/Ubuntu/Debug' $HOME/.profile
sed -i '$ a\export JOHNNY_DEPS=$JOHNNY_ROOT/dependencies' $HOME/.profile
sed -i '$ a\export JOHNNY_DEPS_INCLUDE=$JOHNNY_DEPS/include' $HOME/.profile
sed -i '$ a\export JOHNNY_DEPS_LIB=$JOHNNY_DEPS/lib/Ubuntu' $HOME/.profile

echo Done Writing environment variables!
echo Please logout and login