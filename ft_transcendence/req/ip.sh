#!/bin/bash
NEW_IP=$(ifconfig en0 | grep 'inet ' | awk '{print $2}')
ENV_FILE="req/.env"

if grep -q "^IP_HOST_DOCKER=" "$ENV_FILE"; then
    sed -i.old "s/^IP_HOST_DOCKER=.*/IP_HOST_DOCKER=$NEW_IP/" $ENV_FILE 
    rm req/.env.old
else
    echo -e "\nIP_HOST_DOCKER=$NEW_IP" >> "$ENV_FILE"
fi