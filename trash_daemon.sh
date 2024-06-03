#!/bin/bash

TRASH_DIR="/tmp/trash"
STOP_FILE="${TRASH_DIR}/stop.trash"

# Function to delete .trash files in the trash directory
delete_trash_files() {
  find "${TRASH_DIR}" -type f -name '*.trash' -not -name 'stop.trash' -exec rm {} \;
}

# Check if the stop file exists, if it does, exit the script
if [ -f "${STOP_FILE}" ]; then
  echo "Stop file found, exiting..."
  exit 0
fi

# Main loop that runs every 30 seconds
while true; do
  echo "Deleting .trash files..."
  delete_trash_files
  echo "Sleeping for 30 seconds..."
  sleep 30
done
