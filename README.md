# Minix for dummies

... or something.

## Installing and running using QEMU

1. Download the latest version of Minix:

    ```sh
    wget http://download.minix3.org/iso/minix_R3.3.0-588a35b.iso.bz2
    ```

2. Create an empty disk image:

    ```sh
    qemu-img create -f raw minix.img 10G
    ```

3. Install Minix to the empty image:

    ```sh
    qemu-system-x86_64 -rtc base=utc -cpu host -enable-kvm -boot d -cdrom minix_R3.3.0-588a35b.iso -drive file=minix.img,format=raw -m 1G -smp 2
    ```

    > Note: when choosing a network card, specify the "Virtio network device" number.

4. Start the newly installed system:

    ```sh
    qemu-system-x86_64 -rtc base=utc -cpu host -enable-kvm -boot a -drive file=minix.img,format=raw-m 1G -smp 2
    ```

5. Login as `root`
6. Edit `/boot.cfg` to add `$args cttyline=0 virtio_blk=yes` at the end of your entry of choice
7. Run `/bin/update_bootcfg` and `shutdown -h now`
8. Now, restart the machine using

    ```sh
    qemu-system-x86_64 -rtc base=utc -nic user,model=virtio,hostfwd=tcp::2222-:22 -cpu host -enable-kvm -boot a -drive file=minix.img,format=raw,if=virtio -serial mon:stdio -m 1G -smp 2
    ```

9. Login as `root` again, and setup your machine following [the guide](https://wiki.minix3.org/doku.php?id=usersguide:postinstallation)
10. Now, after setting up `sshd` we can `reboot` the machine and use `ssh` to login:

    ```sh
    ssh root@localhost -p 2222
    ```

## How-to's

### Transfer files

To transfer files simply install `rsync` (`pkgin in rsync`) and use it as:

```sh
rsync -avzh --progress [SRC] -e 'ssh -p 2222' root@localhost:[DEST]
```

> Note: `rsync` must be installed on the guest and the host.
