# 2.2.7 Зберегти всі команди керування віртуальною машиною, які було виконано у попередніх пунктах, у файлі CreateVMSurname.sh, де Surname – ваше прізвище транслітерацією, наприклад «CreateVMBlazhko.sh»;

VBoxManage createvm --name "Ubuntu of Karaulnyi 2" --register

VBoxManage modifyvm "Ubuntu of Karaulnyi 2" --memory 2422

VBoxManage modifyvm "Ubuntu of Karaulnyi 2" \
--graphicscontroller=vboxvga --vram 128

VBoxManage modifyvm "Ubuntu of Karaulnyi 2" --nic1 nat

VBoxManage storagectl "Ubuntu of Karaulnyi 2" --name "KaraulnyiSATA" \
--add sata --controller IntelAHCI

VBoxManage storagectl "Ubuntu of Karaulnyi 2" --name "KaraulnyiIDE" \
--add ide --controller PIIX4

VBoxManage createmedium --filename "DiskKaraulnyi.vdi" --size 9640

VBoxManage storageattach "Ubuntu of Karaulnyi 2" \
--storagectl "KaraulnyiSATA" --port 0 --device 0 --type hdd \
--medium "DiskKaraulnyi.vdi"

VBoxManage storageattach "Ubuntu of Karaulnyi 2" \
--storagectl "KaraulnyiIDE" --port 0 --device 0 --type dvddrive \
--medium "D:\OS_WORK\ubuntu-14.04.6-server-amd64.iso"

VBoxManage startvm "Ubuntu of Karaulnyi 2"

VBoxManage controlvm "Ubuntu of Karaulnyi 2" poweroff

VBoxManage unregistervm "Ubuntu of Karaulnyi 2" --delete --delete-all
