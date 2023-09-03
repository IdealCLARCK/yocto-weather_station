# About The Project


This project serves as a training exercise focused on utilizing Yocto to emulate a variety of sensors and actuators in a smart home environment.


## Project Structure

    ├── Yocto-labs                      # Yocto environment
    │   ├── layers                      # Layer descriptions
    │   ├── builds                      # Build configurations and output
    │   ├── downloads                   # Downloaded source code and files
    │   └── sstate-cache                # Shared state cache
    └── prebuilt_binaries               # Precompiled binaries for testing on x86_64 or ARM architecture


## Yocto informations

 ### Architecture

The QEMU instance used in this project is based on the "qemuarm" architecture. If you choose to use your own, ensure it matches the same architecture



 ### Users and Passwords

    username: root - pwd: linux
    username: guest - pwd: welcome - (not used here) 





## Quick test with prebuilt binaries


### Test on x86_64 architecture

To test the services, open three terminals and run the following commands:

    ./service1
    ./service2
    ./service3

You can see the print of the services in their respective terminal


### Test on qemuarm architecture

Once your QEMU instance is up and running, copy the prebuilt service files to the QEMU environment using the following command:

    scp service1_arm service2_arm service3_arm root@192.168.7.2:/tmp/

Now that the files are copied, you can run the services in the background using:

    ./service1 &
    ./service2 &
    ./service3 &

You can see the log output using :

    cat /var/log/messages




# Building yocto image

If you wish to build the Yocto image from scratch, follow these steps.



## My yocto recipes structure

The services will be built and launched automatically when building the image. The recipes files are organized as following :

    ├── ...
    ├── layers
    │   ├── meta-my-layer                  # Custom layer folder
    │   │   ├── recipes-custom            # Folder for custom recipes
    │   │   │  ├── services               # Recipes to build services
    │   │   │  ├── services-startup       # Recipes that sets services startup scripts
    │   │   └── ...
    │   └── ...
    └── ...



## Initialize the environment

First, initialize the Yocto environment with the following command:

    source layers/poky/oe-init-build-env builds/build-qemu



## Build your image

Build your Yocto image by running the following command:

    bitbake my-image



## Running QEMU

To run your Yocto image on QEMU, execute the following command:

    runqemu nographic my-image



## Logging in

Log in as the root user.



## View service logs on QEMU

To access the service logs on QEMU, use the following command:

    cat /var/log/messages




# Improvements

To enhance the project further, consider the following:

    Improve readme readability
    Improved log readability on QEMU
    Handling errors when a message couldn't be sent
    Compute checksums for the my-layer