#!/bin/bash

# Loop to create 30 users
for i in {1..30}
do
    # Create a user with the username user1, user2, ..., user30
    sudo adduser --disabled-password --gecos "" user$i

    # Set the password for each user (password1, password2, ..., password30)
    echo "user$i:password$i" | sudo chpasswd
done

echo "30 users created with usernames user1 to user30 and passwords password1 to password30"