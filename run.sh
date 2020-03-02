if docker ps -a |grep -q pld-comp ; then
    echo "Container is already running"
else
    echo "Container not started"
    echo "Starting container..."
    docker run --rm --name pld-comp -v $(pwd):/pld-comp -t -d -w /pld-comp eguerin/antlr4cpp
    echo "Container started"
fi

echo "Entering container using bash"
docker exec -it pld-comp bash