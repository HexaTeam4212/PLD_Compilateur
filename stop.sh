if docker ps -a |grep -q pld-comp ; then
    echo "Stopping container..."
    docker stop pld-comp
    echo "Container stopped"
else
    echo "Container already stopped"
fi