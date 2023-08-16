# pam_ipcisolation

Create a new IPC namespace on session creation.

That's it.

### Building

Make sure you have the development package for libpam installed. The package is called `libpam0g-dev` under Debian. Then run:
```shell
make
```

### Install

Build first, then install with root privileges:
```shell
make
sudo make install
```

Finally, add a corresponding line to PAM:
```shell
echo 'session optional pam_ipcisolation.so' | sudo tee -a /etc/pam.d/common-session
```

### Fully isolating IPC

This module creates a new IPC namespace.
Note that it does that and nothing else.
It does not create a new mount namespace and mount over `/dev/mqueue` or `/dev/shm` in order to fully isolate POSIX message queues or POSIX shared memory regions.
pam_namespace might be a good choice for that job:
```shell
echo '/dev/mqueue  /tmp/mqueue-inst  user  root' | sudo tee -a /etc/security/namespace.conf
echo '/dev/shm     /tmp/shm-inst     user  root' | sudo tee -a /etc/security/namespace.conf

# Enable pam_namespace:
echo 'session optional pam_namespace.so' | sudo tee -a /etc/pam.d/common-session
```
