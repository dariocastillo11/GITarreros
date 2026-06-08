# Informe del Trabajo Práctico N°4

## Kernel-modules

Se instalan los paquetes, compiladores y codigo fuente necesarios.
```bash 
~/Documentos/facu/actuales/priSem/SdeC > sudo apt install build-essential checkinstall linux-source
Leyendo lista de paquetes... Hecho
Creando árbol de dependencias... Hecho
Leyendo la información de estado... Hecho
build-essential ya está en su versión más reciente (12.10ubuntu1).
checkinstall ya está en su versión más reciente (1.6.2+git20170426.d24a630-4).
linux-source ya está en su versión más reciente (6.8.0-124.124).
Los paquetes indicados a continuación se instalaron de forma automática y ya no son necesarios.
  libllvm19 libwayland-server0:i386 linux-headers-6.8.0-57 linux-headers-6.8.0-57-generic linux-image-6.8.0-57-generic
  linux-modules-6.8.0-57-generic linux-modules-extra-6.8.0-57-generic linux-tools-6.8.0-57 linux-tools-6.8.0-57-generic
Utilice «sudo apt autoremove» para eliminarlos.
0 actualizados, 0 nuevos se instalarán, 0 para eliminar y 440 no actualizados.
```

Se instalan las headers específicas para la versión del kernel del equipo.
```bash
~/Documentos/facu/actuales/priSem/SdeC/tp4 > sudo apt install linux-headers-$(uname -r)                                             6s
[sudo] contraseña para joaquin:           
Leyendo lista de paquetes... Hecho
Creando árbol de dependencias... Hecho
Leyendo la información de estado... Hecho
linux-headers-6.8.0-124-generic ya está en su versión más reciente (6.8.0-124.124).
fijado linux-headers-6.8.0-124-generic como instalado manualmente.
Los paquetes indicados a continuación se instalaron de forma automática y ya no son necesarios.
  libllvm19 libwayland-server0:i386 linux-headers-6.8.0-57 linux-headers-6.8.0-57-generic linux-image-6.8.0-57-generic
  linux-modules-6.8.0-57-generic linux-modules-extra-6.8.0-57-generic linux-tools-6.8.0-57 linux-tools-6.8.0-57-generic
Utilice «sudo apt autoremove» para eliminarlos.
0 actualizados, 0 nuevos se instalarán, 0 para eliminar y 440 no actualizados.
```
Se incorpora el submódulo.
```bash
~/Do/facu/actuales/priSem/SdeC/GITarreros/tp4 joaquin +2 !1 ?1 > git submodule add git@gitlab.com:joa.suarez/kernel-modules.git 
Clonando en '/home/joaquin/Documentos/facu/actuales/priSem/SdeC/GITarreros/tp4/kernel-modules'...
remote: Enumerating objects: 14, done.
remote: Total 14 (delta 0), reused 0 (delta 0), pack-reused 14 (from 1)
Recibiendo objetos: 100% (14/14), 4.76 KiB | 4.76 MiB/s, listo.
```
Se accede a la carpeta específica del módulo
```bash
~/Do/facu/actuales/priSem/SdeC/GITarreros/tp4 joaquin +2 !1 ?3 > cd kernel-modules/part1/module   
```
Se compila el código fuente 
```bash
~/Do/f/ac/p/S/GITarreros/tp4/kernel-modules/p/module joaquin !1 > make      
make -C /lib/modules/6.8.0-124-generic/build M=/home/joaquin/Documentos/facu/actuales/priSem/SdeC/GITarreros/tp4/kernel-modules/part1/module modules
make[1]: se entra en el directorio '/usr/src/linux-headers-6.8.0-124-generic'
warning: the compiler differs from the one used to build the kernel
  The kernel was built by: x86_64-linux-gnu-gcc-13 (Ubuntu 13.3.0-6ubuntu2~24.04.1) 13.3.0
  You are using:           gcc-13 (Ubuntu 13.3.0-6ubuntu2~24.04.1) 13.3.0
  CC [M]  /home/joaquin/Documentos/facu/actuales/priSem/SdeC/GITarreros/tp4/kernel-modules/part1/module/mimodulo.o
/home/joaquin/Documentos/facu/actuales/priSem/SdeC/GITarreros/tp4/kernel-modules/part1/module/mimodulo.c:8:5: warning: no previous prototype for ‘modulo_lin_init’ [-Wmissing-prototypes]
    8 | int modulo_lin_init(void)
      |     ^~~~~~~~~~~~~~~
/home/joaquin/Documentos/facu/actuales/priSem/SdeC/GITarreros/tp4/kernel-modules/part1/module/mimodulo.c:17:6: warning: no previous prototype for ‘modulo_lin_clean’ [-Wmissing-prototypes]
   17 | void modulo_lin_clean(void)
      |      ^~~~~~~~~~~~~~~~
  MODPOST /home/joaquin/Documentos/facu/actuales/priSem/SdeC/GITarreros/tp4/kernel-modules/part1/module/Module.symvers
  CC [M]  /home/joaquin/Documentos/facu/actuales/priSem/SdeC/GITarreros/tp4/kernel-modules/part1/module/mimodulo.mod.o
  LD [M]  /home/joaquin/Documentos/facu/actuales/priSem/SdeC/GITarreros/tp4/kernel-modules/part1/module/mimodulo.ko
  BTF [M] /home/joaquin/Documentos/facu/actuales/priSem/SdeC/GITarreros/tp4/kernel-modules/part1/module/mimodulo.ko
Skipping BTF generation for /home/joaquin/Documentos/facu/actuales/priSem/SdeC/GITarreros/tp4/kernel-modules/part1/module/mimodulo.ko due to unavailability of vmlinux
make[1]: se sale del directorio '/usr/src/linux-headers-6.8.0-124-generic'
~/Do/f/ac/p/S/GITarreros/tp4/kernel-modules/p/module joaquin !1 > 
```

Se inserta el modulo en el kernel: 
```bash
~/Do/f/ac/p/S/GITarreros/tp4/kernel-modules/p/module joaquin !1 > sudo insmod mimodulo.ko
~/Do/f/ac/p/S/GITarreros/tp4/kernel-modules/p/module joaquin !1 > 
```
Revisa los logs del kernel
```bash
~/Do/f/ac/p/S/GITarreros/tp4/kernel-modules/p/module joaquin !1 > sudo dmesg | tail      
[   21.564002] usbhid: USB HID core driver
[   35.963222] systemd-journald[294]: Time jumped backwards, rotating.
[  312.068499] iwlwifi 0000:00:14.3: Unhandled alg: 0x703
[ 4015.473153] warning: `ThreadPoolForeg' uses wireless extensions which will stop working for Wi-Fi 7 hardware; use nl80211
[ 8377.740242] mimodulo: module verification failed: signature and/or required key missing - tainting kernel
[ 8377.740801] Modulo cargado en el kernel.
[ 8710.823116] Modulo descargado del kernel.
[13749.625818] Modulo cargado en el kernel.
[13771.920626] Modulo descargado del kernel.
[13810.862222] Modulo cargado en el kernel.
~/Do/f/ac/p/S/GITarreros/tp4/kernel-modules/p/module joaquin !1 > 
```
Se comprueba que está en la lista
```bash
~/Do/f/ac/p/S/GITarreros/tp4/kernel-modules/p/module joaquin !1 > lsmod | grep mimodulo
mimodulo               12288  0
~/Do/f/ac/p/S/GITarreros/tp4/kernel-modules/p/module joaquin !1 > 
```
Se lee la informacion del módulo
```bash
~/Do/f/ac/p/S/GITarreros/tp4/kernel-modules/p/module joaquin !1 > modinfo mimodulo.ko 
filename:       /home/joaquin/Documentos/facu/actuales/priSem/SdeC/GITarreros/tp4/kernel-modules/part1/module/mimodulo.ko
author:         Catedra de SdeC
description:    Primer modulo ejemplo
license:        GPL
srcversion:     C6390D617B2101FB1B600A9
depends:        
retpoline:      Y
name:           mimodulo
vermagic:       6.8.0-124-generic SMP preempt mod_unload modversions 
~/Do/f/ac/p/S/GITarreros/tp4/kernel-modules/p/module joaquin !1 > 
```
Se genera un par de claves criptográficas 
```bash
~/Do/f/ac/p/S/GITarreros/tp4/kernel-modules/p/module joaquin !1 > openssl req -new -x509 -newkey rsa:2048 -keyout clave_privada.priv -outform DER -out certificado.der -nodes -days 3650 -subj "/CN=Clave De Joaquin/"
...+...............+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*..........+.......+.........+.....+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*.......+....+.....+.+......+...........+............+...+....+...+......+.....+......+.+...+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
.+...+.+.................+..........+..+......+.........+......+.+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*.............+.............+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*..+...........+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
-----
~/Do/f/ac/p/S/GITarreros/tp4/kernel-modules/p/module joaquin !1 > 
```
Se firma digitalmente el archivo .ko 
```bash
~/Do/f/ac/p/S/GITarreros/tp4/kernel-modules/p/module joaquin !1 > sudo /usr/src/linux-headers-$(uname -r)/scripts/sign-file sha512 clave_privada.priv certificado.der mimodulo.ko
~/Do/f/ac/p/S/GITarreros/tp4/kernel-modules/p/module joaquin !1 > 
```
Se verifica que la firma se ha puesto en el módulo
```bash
~/Do/f/ac/p/S/GITarreros/tp4/kernel-modules/p/module joaquin !1 > modinfo mimodulo.ko
filename:       /home/joaquin/Documentos/facu/actuales/priSem/SdeC/GITarreros/tp4/kernel-modules/part1/module/mimodulo.ko
author:         Catedra de SdeC
description:    Primer modulo ejemplo
license:        GPL
srcversion:     C6390D617B2101FB1B600A9
depends:        
retpoline:      Y
name:           mimodulo
vermagic:       6.8.0-124-generic SMP preempt mod_unload modversions 
sig_id:         PKCS#7
signer:         Clave De Joaquin
sig_key:        48:A5:1E:D8:56:28:66:FE:50:F9:00:8A:A7:97:73:01:F0:19:99:CC
sig_hashalgo:   sha512
signature:      0E:D3:5F:74:AC:D2:51:BE:7D:1B:93:B2:9C:78:73:EB:24:43:04:F5:
		40:64:0F:91:5F:87:5C:5D:7F:9D:32:9D:E0:17:B5:1A:13:93:1E:39:
		43:40:35:DC:28:E1:66:25:31:54:16:2E:38:7E:16:BA:84:12:94:F7:
		94:91:42:A0:5B:47:C2:DE:B0:8D:E9:44:2D:58:E4:A3:37:D8:96:E9:
		3B:03:52:28:08:46:DF:C3:52:38:B0:E7:03:24:B2:07:6C:EB:AD:E6:
		C7:CE:43:F7:76:F4:3B:85:68:4E:53:85:B2:86:E5:2C:5C:E7:24:23:
		A6:86:8D:42:FA:6E:10:4A:E3:88:77:C3:17:D8:2B:AD:14:C6:D9:2B:
		40:4F:66:99:23:58:D7:44:B8:72:23:02:47:37:4F:54:23:60:BA:D2:
		ED:01:09:E7:E9:63:20:D6:04:1C:39:79:02:19:F4:C6:85:75:F7:1D:
		E1:74:7F:02:E0:69:6F:0F:41:6D:21:D9:32:93:E7:46:3D:3C:91:DF:
		7C:C4:11:17:F1:DB:58:84:C2:66:FA:4A:92:31:D6:0C:83:3C:99:ED:
		92:BA:7B:90:42:07:73:2B:E3:B7:17:15:19:A4:69:F7:36:B5:70:94:
		93:DB:F3:BB:A0:21:2C:14:B1:F6:1B:32:0E:EB:1B:19
~/Do/f/ac/p/S/GITarreros/tp4/kernel-modules/p/module joaquin !1 >
```
Se muestra un módulo oficial para tener una referencia:
```bash
~/Do/f/ac/p/S/GITarreros/tp4/kernel-modules/p/module joaquin !1 > modinfo des_generic                                          
filename:       /lib/modules/6.8.0-124-generic/kernel/crypto/des_generic.ko.zst
alias:          crypto-des3_ede-generic
alias:          des3_ede-generic
alias:          crypto-des3_ede
alias:          des3_ede
alias:          crypto-des-generic
alias:          des-generic
alias:          crypto-des
alias:          des
author:         Dag Arne Osvik <da@osvik.no>
description:    DES & Triple DES EDE Cipher Algorithms
license:        GPL
srcversion:     B56606AD918CF0074D320DB
depends:        libdes
retpoline:      Y
intree:         Y
name:           des_generic
vermagic:       6.8.0-124-generic SMP preempt mod_unload modversions 
sig_id:         PKCS#7
signer:         Build time autogenerated kernel key
sig_key:        52:C8:5D:A1:6E:10:83:FF:2A:CF:96:CB:FE:D8:62:D5:AF:46:85:0E
sig_hashalgo:   sha512
signature:      AE:81:1B:21:6F:7B:E2:6B:BD:BF:E2:74:AE:E4:DC:49:29:01:B5:CF:
		81:99:D5:C7:50:89:4E:DE:DD:02:33:03:90:A1:96:90:4A:46:1F:F0:
		6B:15:DD:C9:38:81:C4:DC:9A:24:08:C3:42:C6:57:DF:58:FC:97:92:
		7C:2B:90:E7:2A:30:68:0A:A6:E1:0D:63:28:DA:37:02:24:38:B2:26:
		57:39:D5:69:10:D2:2F:E4:91:7F:21:E2:75:91:38:27:DE:57:96:ED:
		39:59:25:F8:A5:7A:41:75:19:9A:AF:3A:D2:C0:4A:A0:A0:F8:52:52:
		D6:B9:BB:DD:3D:F1:29:37:16:7D:AC:84:F3:98:15:23:CB:06:D0:6B:
		16:64:E1:3C:B1:8E:49:72:CE:7F:E2:B0:E9:69:DB:E8:26:11:EC:7B:
		D4:ED:C9:F3:7C:89:34:3F:62:FE:DE:82:9D:D2:53:4D:66:16:3A:5C:
		0A:7F:F2:59:D3:E7:5C:15:B2:C5:BF:EB:C6:62:9E:91:54:F4:2C:96:
		DF:24:D1:22:4B:3B:9F:F8:D4:95:84:9F:38:D7:B8:3F:ED:FF:EA:26:
		EA:18:E4:FC:B8:A3:6C:9F:9A:4B:C6:DD:2A:C3:2A:37:15:19:E5:5A:
		86:43:B5:F2:7D:71:86:C1:46:E3:77:5F:71:03:38:A1:84:ED:E6:BD:
		6B:1C:33:E7:60:4C:8A:3C:7B:BC:0B:F8:EE:E7:44:72:81:FA:3A:C2:
		E3:1F:6E:09:AB:29:32:50:A2:DC:3E:A2:46:C3:65:F6:F3:E3:83:63:
		C2:44:D3:57:26:97:0D:7F:E4:2A:45:F6:39:4E:EA:BB:88:02:23:4B:
		95:25:60:58:51:4D:C3:24:E5:15:B6:5C:50:C9:E7:86:C4:23:E6:56:
		3A:66:3A:B3:79:3D:7B:70:0A:7A:8B:5E:5B:C1:2B:8D:81:91:25:73:
		88:BE:E2:78:10:59:61:7B:4F:EF:BD:9A:6F:12:D9:A3:BA:72:23:7C:
		E2:78:A0:E1:F4:28:40:A9:58:5E:1A:BF:CE:4B:40:70:80:90:EF:54:
		7A:70:F5:90:97:33:9F:EE:DD:E1:6B:57:1D:38:6A:BB:BB:5B:98:BC:
		15:2C:96:39:0C:68:33:82:1D:14:F4:AC:A2:CC:79:DD:CD:F7:2C:B1:
		D5:76:1B:4F:9F:13:47:44:EA:83:52:F5:1D:3B:EB:81:91:A3:02:F1:
		18:54:DE:E9:CB:5F:32:1B:7D:4B:9C:7A:40:2E:7B:E3:03:50:3C:FB:
		DB:0E:5A:1B:5E:7C:92:77:81:1F:AF:C6:9D:FA:0D:4E:98:DF:66:41:
		CE:2A:22:B0:03:E9:63:4A:C0:57:36:F6
~/Do/f/ac/p/S/GITarreros/tp4/kernel-modules/p/module joaquin !1 > 
```

### ¿Qué diferencias se pueden observar entre los dos módulos?

El comando `modinfo` extrae información incrustada dentro de un módulo de kernel. Al comparar ambos, saltan a la vista varias diferencias fundamentales:

* **Campo Intree:**
  * **`mimodulo`**: No lo tiene. Esto indica que es un módulo compilado fuera del código fuente oficial del kernel (*out-of-tree*). Es por eso que al cargar el módulo sale el mensaje *"tainting kernel"*.
  * **`des_generic`**: Tiene el valor `Y` (Yes). Significa que es un módulo oficial que se compila y distribuye junto con el propio núcleo de Linux.

* **Firma:**
  * **`mimodulo`**: Está firmado con una clave personalizada.
  * **`des_generic`**: Está firmado por la clave generada automáticamente durante la compilación del kernel de Linux.

* **Dependencias:**
  * **`mimodulo`**: Está vacío. Es completamente autónomo y debe ser cargado manualmente, ya que no posee alias configurados.
  * **`des_generic`**: Depende de `libdes`. Si se quiere cargar `des_generic` sin cargar `libdes` primero, el kernel no lo va a permitir.

* **Alias:**
  * **`mimodulo`**: No tiene alias.
  * **`des_generic`**: Tiene varios nombres alternativos (`crypto-des`, `des3_ede`, etc.) que otros programas pueden usar para solicitar sus servicios sin saber el nombre exacto del archivo.

---

### ¿Qué drivers/módulos están cargados en sus propias pc? 

Al inspeccionar los sistemas, algunos drivers cargados que se pueden observar son: 

```bash
bluetooth            1036288  42 btrtl,btmtk,btintel,btbcm,bnep,btusb,rfcomm
usbhid                 77824  0
video                  77824  4 dell_wmi,dell_laptop,xe,i915
```

### ¿Por qué es distinta en cada computadora? 
Porque cada computadora tiene componentes distintos, y Linux carga en memoria únicamente los drivers/módulos que necesita..

Las diferencias, como se dijo, ocurren por el hardware. El kernel detecta automáticamente qué componentes físicos tiene la máquina (placa de video, tipo de procesador, periféricos) y carga únicamente los módulos (drivers) necesarios para hacerlos funcionar.

Con una placa de video **NVIDIA**, se tienen módulos como `nvidia` o `nouveau`. Con **Intel**, `i915`.

Con una placa Wi-Fi **Realtek**, se tendrá el módulo `rtw88_core`, mientras que con **Intel** se tendrá `iwlwifi`.

Incluso varían los sistemas de archivos en uso o si se usan máquinas virtuales (que cargan módulos como `vboxdrv` o `kvm`).

Diff: 
```bash
====
1:2,31c
  mimodulo               12288  0
  usbhid                 77824  0
  nf_conntrack_netlink    57344  0
  xt_nat                 12288  10
  xt_tcpudp              16384  0
  veth                   45056  0
  xt_conntrack           12288  2
  xt_MASQUERADE          16384  2
  bridge                425984  0
  stp                    12288  1 bridge
  llc                    16384  2 bridge,stp
  xfrm_user              61440  1
  xfrm_algo              16384  1 xfrm_user
  xt_set                 20480  0
  ip_set                 61440  1 xt_set
  nft_chain_nat          12288  9
  nf_nat                 61440  3 xt_nat,nft_chain_nat,xt_MASQUERADE
  nf_conntrack          196608  5 xt_conntrack,nf_nat,xt_nat,nf_conntrack_netlink,xt_MASQUERADE
  nf_defrag_ipv6         24576  1 nf_conntrack
  nf_defrag_ipv4         12288  1 nf_conntrack
  xt_addrtype            12288  4
  nft_compat             20480  18
  vxlan                 155648  0
  ip6_udp_tunnel         16384  1 vxlan
  udp_tunnel             32768  1 vxlan
  ccm                    20480  9
  rfcomm                102400  16
  overlay               212992  2
  qrtr                   53248  2
  nf_tables             380928  202 nft_compat,nft_chain_nat
2:2,25c
  veth                   45056  0
  nf_conntrack_netlink    57344  0
  xt_nat                 12288  10
  xt_tcpudp              16384  0
  xt_conntrack           12288  5
  xt_MASQUERADE          16384  5
  bridge                425984  0
  stp                    12288  1 bridge
  llc                    16384  2 bridge,stp
  xfrm_user              65536  1
  xfrm_algo              16384  1 xfrm_user
  xt_set                 20480  0
  ip_set                 61440  1 xt_set
  nft_chain_nat          12288  9
  nf_nat                 61440  3 xt_nat,nft_chain_nat,xt_MASQUERADE
  nf_conntrack          192512  5 xt_conntrack,nf_nat,xt_nat,nf_conntrack_netlink,xt_MASQUERADE
  nf_defrag_ipv6         24576  1 nf_conntrack
  nf_defrag_ipv4         12288  1 nf_conntrack
  xt_addrtype            12288  4
  nft_compat             20480  24
  nf_tables             385024  271 nft_compat,nft_chain_nat
  rfcomm                 98304  4
  snd_seq_dummy          12288  0
  snd_hrtimer            12288  1
3:2,10c
  ccm                    20480  3
  rfcomm                 98304  4
  snd_seq_dummy          12288  0
  snd_hrtimer            12288  1
  snd_seq_midi           24576  0
  snd_seq_midi_event     16384  1 snd_seq_midi
  snd_rawmidi            57344  1 snd_seq_midi
  snd_seq               122880  9 snd_seq_midi,snd_seq_midi_event,snd_seq_dummy
  snd_seq_device         16384  3 snd_seq,snd_seq_midi,snd_rawmidi
====1
1:33c
  algif_hash             12288  1
2:27c
3:12c
  algif_hash             16384  1
====
1:35a
2:30,32c
  ccm                    20480  6
  overlay               221184  2
  qrtr                   53248  2
3:15c
  qrtr                   53248  2
====
1:37,92c
  binfmt_misc            24576  1
  zfs                  6602752  6
  spl                   180224  1 zfs
  xe                   2727936  0
  snd_hda_codec_cs8409    36864  1
  snd_hda_codec_generic   122880  1 snd_hda_codec_cs8409
  drm_gpuvm              45056  1 xe
  drm_exec               12288  2 drm_gpuvm,xe
  gpu_sched              61440  1 xe
  drm_suballoc_helper    16384  1 xe
  drm_ttm_helper         12288  1 xe
  snd_sof_pci_intel_tgl    12288  0
  snd_sof_intel_hda_common   217088  1 snd_sof_pci_intel_tgl
  soundwire_intel        73728  1 snd_sof_intel_hda_common
  snd_sof_intel_hda_mlink    45056  2 soundwire_intel,snd_sof_intel_hda_common
  soundwire_cadence      45056  1 soundwire_intel
  snd_sof_intel_hda      24576  1 snd_sof_intel_hda_common
  snd_hda_codec_hdmi     94208  1
  snd_sof_pci            24576  2 snd_sof_intel_hda_common,snd_sof_pci_intel_tgl
  snd_sof_xtensa_dsp     12288  1 snd_sof_intel_hda_common
  snd_sof               380928  3 snd_sof_pci,snd_sof_intel_hda_common,snd_sof_intel_hda
  snd_sof_utils          16384  1 snd_sof
  snd_soc_hdac_hda       24576  1 snd_sof_intel_hda_common
  snd_hda_ext_core       32768  4 snd_sof_intel_hda_common,snd_soc_hdac_hda,snd_sof_intel_hda_mlink,snd_sof_intel_hda
  snd_soc_acpi_intel_match    98304  2 snd_sof_intel_hda_common,snd_sof_pci_intel_tgl
  snd_soc_acpi           16384  2 snd_soc_acpi_intel_match,snd_sof_intel_hda_common
  soundwire_generic_allocation    12288  1 soundwire_intel
  soundwire_bus         110592  3 soundwire_intel,soundwire_generic_allocation,soundwire_cadence
  snd_soc_core          442368  4 soundwire_intel,snd_sof,snd_sof_intel_hda_common,snd_soc_hdac_hda
  intel_uncore_frequency    16384  0
  intel_uncore_frequency_common    16384  1 intel_uncore_frequency
  snd_compress           28672  1 snd_soc_core
  ac97_bus               12288  1 snd_soc_core
  snd_pcm_dmaengine      16384  1 snd_soc_core
  snd_hda_intel          61440  3
  snd_intel_dspcfg       36864  3 snd_hda_intel,snd_sof,snd_sof_intel_hda_common
  snd_intel_sdw_acpi     16384  2 snd_sof_intel_hda_common,snd_intel_dspcfg
  x86_pkg_temp_thermal    20480  0
  snd_hda_codec         204800  6 snd_hda_codec_generic,snd_hda_codec_hdmi,snd_hda_codec_cs8409,snd_hda_intel,snd_soc_hdac_hda,snd_sof_intel_hda
  snd_hda_core          139264  9 snd_hda_codec_generic,snd_hda_codec_hdmi,snd_hda_codec_cs8409,snd_hda_intel,snd_hda_ext_core,snd_hda_codec,snd_sof_intel_hda_common,snd_soc_hdac_hda,snd_sof_intel_hda
  snd_hwdep              20480  1 snd_hda_codec
  snd_pcm               192512  11 snd_hda_codec_hdmi,snd_hda_intel,snd_hda_codec,soundwire_intel,snd_sof,snd_sof_intel_hda_common,snd_compress,snd_soc_core,snd_sof_utils,snd_hda_core,snd_pcm_dmaengine
  intel_powerclamp       24576  0
  i915                 4288512  21
  coretemp               24576  0
  snd_seq_midi           24576  0
  btusb                  81920  0
  cmdlinepart            12288  0
  kvm_intel             487424  0
  iwlmvm                868352  0
  btrtl                  32768  1 btusb
  snd_seq_midi_event     16384  1 snd_seq_midi
  uvcvideo              147456  0
  spi_nor               163840  0
  btintel                57344  1 btusb
  btbcm                  24576  1 btusb
2:34,54c
  amdgpu              20107264  26
  snd_hda_codec_conexant    32768  1
  snd_hda_codec_atihdmi    24576  1
  snd_hda_codec_generic   122880  1 snd_hda_codec_conexant
  snd_hda_codec_hdmi     65536  1 snd_hda_codec_atihdmi
  snd_hda_intel          61440  2
  snd_hda_codec         204800  5 snd_hda_codec_generic,snd_hda_codec_conexant,snd_hda_codec_hdmi,snd_hda_intel,snd_hda_codec_atihdmi
  snd_hda_core          143360  6 snd_hda_codec_generic,snd_hda_codec_conexant,snd_hda_codec_hdmi,snd_hda_intel,snd_hda_codec,snd_hda_codec_atihdmi
  intel_rapl_msr         20480  0
  amd_atl                69632  1
  snd_intel_dspcfg       45056  1 snd_hda_intel
  intel_rapl_common      53248  1 intel_rapl_msr
  snd_intel_sdw_acpi     16384  1 snd_intel_dspcfg
  snd_hwdep              24576  1 snd_hda_codec
  snd_pcm               200704  4 snd_hda_codec_hdmi,snd_hda_intel,snd_hda_codec,snd_hda_core
  edac_mce_amd           28672  0
  rtw88_8822ce           12288  0
  rtw88_8822c           512000  1 rtw88_8822ce
  uvcvideo              143360  0
  snd_seq_midi           24576  0
  rtw88_pci              36864  1 rtw88_8822ce
3:17,64c
  snd_hda_codec_intelhdmi    24576  1
  snd_hda_codec_alc269   139264  1
  snd_hda_scodec_component    20480  1 snd_hda_codec_alc269
  snd_hda_codec_realtek_lib    65536  1 snd_hda_codec_alc269
  snd_hda_codec_generic   122880  2 snd_hda_codec_realtek_lib,snd_hda_codec_alc269
  snd_hda_intel          61440  1
  snd_sof_pci_intel_cnl    20480  0
  snd_sof_intel_hda_generic    36864  1 snd_sof_pci_intel_cnl
  soundwire_intel        81920  1 snd_sof_intel_hda_generic
  snd_sof_intel_hda_sdw_bpt    20480  1 soundwire_intel
  snd_sof_intel_hda_common   188416  3 snd_sof_intel_hda_sdw_bpt,snd_sof_intel_hda_generic,snd_sof_pci_intel_cnl
  intel_uncore_frequency    12288  0
  snd_soc_hdac_hda       20480  1 snd_sof_intel_hda_common
  intel_uncore_frequency_common    20480  1 intel_uncore_frequency
  snd_sof_intel_hda_mlink    45056  4 snd_sof_intel_hda_sdw_bpt,soundwire_intel,snd_sof_intel_hda_common,snd_sof_intel_hda_generic
  intel_pmc_core_pltdrv    12288  0
  snd_sof_intel_hda      24576  2 snd_sof_intel_hda_common,snd_sof_intel_hda_generic
  intel_pmc_core        135168  0
  snd_hda_codec_hdmi     65536  1 snd_hda_codec_intelhdmi
  pmt_telemetry          16384  1 intel_pmc_core
  pmt_discovery          20480  1 pmt_telemetry
  soundwire_cadence      49152  1 soundwire_intel
  pmt_class              20480  2 pmt_telemetry,pmt_discovery
  snd_sof_pci            24576  2 snd_sof_intel_hda_generic,snd_sof_pci_intel_cnl
  intel_pmc_ssram_telemetry    16384  1 intel_pmc_core
  intel_vsec             24576  2 intel_pmc_ssram_telemetry,pmt_telemetry
  snd_sof_xtensa_dsp     12288  1 snd_sof_intel_hda_generic
  intel_tcc_cooling      12288  0
  snd_sof               401408  6 snd_sof_intel_hda_sdw_bpt,snd_sof_pci,snd_sof_intel_hda_common,snd_sof_intel_hda_generic,snd_sof_intel_hda,snd_sof_pci_intel_cnl
  x86_pkg_temp_thermal    20480  0
  snd_sof_utils          16384  1 snd_sof
  intel_powerclamp       24576  0
  snd_soc_acpi_intel_match   139264  2 snd_sof_intel_hda_generic,snd_sof_pci_intel_cnl
  snd_soc_acpi_intel_sdca_quirks    12288  1 snd_soc_acpi_intel_match
  coretemp               24576  0
  soundwire_generic_allocation    24576  1 soundwire_intel
  snd_soc_acpi           16384  2 snd_soc_acpi_intel_match,snd_sof_intel_hda_generic
  soundwire_bus        1175552  3 soundwire_intel,soundwire_generic_allocation,soundwire_cadence
  snd_soc_sdca           90112  2 snd_soc_acpi_intel_sdca_quirks,soundwire_bus
  kvm_intel             569344  0
  hid                   262144  1 snd_soc_sdca
  crc8                   12288  1 soundwire_cadence
  snd_soc_avs           217088  0
  snd_soc_hda_codec      24576  1 snd_soc_avs
  kvm                  1445888  1 kvm_intel
  uvcvideo              143360  0
  snd_hda_ext_core       32768  7 snd_sof_intel_hda_sdw_bpt,snd_soc_avs,snd_soc_hda_codec,snd_sof_intel_hda_common,snd_soc_hdac_hda,snd_sof_intel_hda_mlink,snd_sof_intel_hda
  binfmt_misc            24576  1
====
1:94,99c
  ee1004                 16384  0
  intel_rapl_msr         20480  0
  mac80211             1744896  1 iwlmvm
  mei_pxp                16384  0
  mei_hdcp               28672  0
  btmtk                  12288  1 btusb
2:56c
  kvm_amd               241664  0
3:66c
  snd_hda_codec         204800  10 snd_hda_codec_generic,snd_soc_avs,snd_hda_codec_hdmi,snd_soc_hda_codec,snd_hda_intel,snd_hda_codec_realtek_lib,snd_soc_hdac_hda,snd_hda_codec_alc269,snd_sof_intel_hda,snd_hda_codec_intelhdmi
====
1:101c
  mtd                    98304  4 spi_nor,cmdlinepart
2:58c
  snd_seq_midi_event     16384  1 snd_seq_midi
3:67a
====
1:103,168c
  libarc4                12288  1 mac80211
  snd_rawmidi            57344  1 snd_seq_midi
  dell_laptop            32768  0
  drm_buddy              20480  2 xe,i915
  kvm                  1404928  1 kvm_intel
  bluetooth            1036288  42 btrtl,btmtk,btintel,btbcm,bnep,btusb,rfcomm
  videobuf2_v4l2         36864  1 uvcvideo
  snd_seq               118784  2 snd_seq_midi,snd_seq_midi_event
  ttm                   110592  3 drm_ttm_helper,xe,i915
  videodev              352256  2 videobuf2_v4l2,uvcvideo
  ecdh_generic           16384  2 bluetooth
  dell_wmi               28672  1 dell_laptop
  iwlwifi               606208  1 iwlmvm
  processor_thermal_device_pci_legacy    12288  0
  irqbypass              12288  1 kvm
  drm_display_helper    237568  2 xe,i915
  processor_thermal_device    20480  1 processor_thermal_device_pci_legacy
  processor_thermal_wt_hint    16384  1 processor_thermal_device
  videobuf2_common       81920  4 videobuf2_vmalloc,videobuf2_v4l2,uvcvideo,videobuf2_memops
  processor_thermal_rfim    32768  1 processor_thermal_device
  cec                    94208  3 drm_display_helper,xe,i915
  ecc                    45056  1 ecdh_generic
  dell_wmi_sysman        49152  0
  rapl                   20480  0
  mc                     81920  4 videodev,videobuf2_v4l2,uvcvideo,videobuf2_common
  dell_smbios            32768  2 dell_wmi,dell_laptop
  processor_thermal_rapl    16384  1 processor_thermal_device
  snd_seq_device         16384  3 snd_seq,snd_seq_midi,snd_rawmidi
  intel_cstate           24576  0
  intel_rapl_common      40960  2 intel_rapl_msr,processor_thermal_rapl
  dcdbas                 20480  1 dell_smbios
  dell_smm_hwmon         32768  0
  snd_timer              49152  2 snd_seq,snd_pcm
  i2c_i801               36864  0
  rc_core                73728  1 cec
  firmware_attributes_class    12288  1 dell_wmi_sysman
  processor_thermal_wt_req    12288  1 processor_thermal_device
  nls_iso8859_1          12288  1
  dell_wmi_descriptor    16384  2 dell_wmi,dell_smbios
  ledtrig_audio          12288  2 dell_wmi,dell_laptop
  wmi_bmof               12288  0
  cfg80211             1368064  3 iwlmvm,iwlwifi,mac80211
  snd                   143360  20 snd_hda_codec_generic,snd_seq,snd_seq_device,snd_hda_codec_hdmi,snd_hwdep,snd_hda_codec_cs8409,snd_hda_intel,snd_hda_codec,snd_sof,snd_timer,snd_compress,snd_soc_core,snd_pcm,snd_rawmidi
  i2c_algo_bit           16384  2 xe,i915
  soundcore              16384  1 snd
  mei_me                 53248  2
  spi_intel_pci          12288  0
  processor_thermal_power_floor    12288  1 processor_thermal_device
  i2c_smbus              16384  1 i2c_i801
  spi_intel              32768  1 spi_intel_pci
  mei                   172032  5 mei_hdcp,mei_pxp,mei_me
  processor_thermal_mbox    12288  4 processor_thermal_power_floor,processor_thermal_wt_req,processor_thermal_rfim,processor_thermal_wt_hint
  intel_soc_dts_iosf     20480  1 processor_thermal_device_pci_legacy
  int3403_thermal        16384  0
  int340x_thermal_zone    16384  2 int3403_thermal,processor_thermal_device
  intel_pmc_core        118784  0
  intel_vsec             20480  1 intel_pmc_core
  int3400_thermal        24576  0
  pmt_telemetry          16384  1 intel_pmc_core
  acpi_thermal_rel       20480  1 int3400_thermal
  intel_hid              32768  0
  pmt_class              12288  1 pmt_telemetry
  acpi_tad               20480  0
  acpi_pad              184320  0
  sparse_keymap          12288  2 intel_hid,dell_wmi
  joydev                 32768  0
2:60,109c
  amdxcp                 12288  1 amdgpu
  rtw88_core            360448  2 rtw88_pci,rtw88_8822c
  drm_panel_backlight_quirks    12288  1 amdgpu
  videobuf2_v4l2         36864  1 uvcvideo
  binfmt_misc            24576  1
  kvm                  1445888  1 kvm_amd
  btusb                  77824  0
  gpu_sched              65536  1 amdgpu
  videobuf2_common       86016  4 videobuf2_vmalloc,videobuf2_v4l2,uvcvideo,videobuf2_memops
  btrtl                  32768  1 btusb
  snd_rawmidi            57344  1 snd_seq_midi
  drm_buddy              28672  1 amdgpu
  ee1004                 16384  0
  mac80211             1851392  2 rtw88_pci,rtw88_core
  irqbypass              16384  1 kvm
  drm_ttm_helper         16384  1 amdgpu
  btintel                69632  1 btusb
  polyval_clmulni        12288  0
  videodev              364544  2 videobuf2_v4l2,uvcvideo
  snd_seq               122880  9 snd_seq_midi,snd_seq_midi_event,snd_seq_dummy
  ghash_clmulni_intel    12288  0
  mmc_block              65536  1
  btbcm                  24576  1 btusb
  ttm                   126976  2 amdgpu,drm_ttm_helper
  aesni_intel            98304  7
  rtsx_usb_ms            24576  0
  snd_seq_device         16384  3 snd_seq,snd_seq_midi,snd_rawmidi
  btmtk                  36864  1 btusb
  drm_exec               12288  1 amdgpu
  gpio_keys              20480  0
  rpmb_core              20480  1 mmc_block
  memstick               28672  1 rtsx_usb_ms
  bluetooth            1032192  34 btrtl,btmtk,btintel,btbcm,bnep,btusb,rfcomm
  mc                     81920  4 videodev,videobuf2_v4l2,uvcvideo,videobuf2_common
  rapl                   20480  0
  nls_iso8859_1          12288  1
  snd_timer              53248  3 snd_seq,snd_hrtimer,snd_pcm
  drm_suballoc_helper    24576  1 amdgpu
  cfg80211             1462272  2 rtw88_core,mac80211
  drm_display_helper    290816  1 amdgpu
  snd                   143360  17 snd_hda_codec_generic,snd_seq,snd_hda_codec_conexant,snd_seq_device,snd_hda_codec_hdmi,snd_hwdep,snd_hda_intel,snd_hda_codec,snd_timer,snd_pcm,snd_rawmidi
  cec                    98304  2 drm_display_helper,amdgpu
  i2c_piix4              32768  0
  rc_core                73728  1 cec
  libarc4                12288  1 mac80211
  k10temp                16384  0
  ccp                   159744  1 kvm_amd
  soundcore              16384  1 snd
  i2c_smbus              20480  1 i2c_piix4
  i2c_algo_bit           16384  1 amdgpu
3:69,150c
  irqbypass              16384  1 kvm
  polyval_clmulni        12288  0
  btusb                  77824  0
  snd_hda_core          143360  13 snd_hda_codec_generic,snd_soc_avs,snd_hda_codec_hdmi,snd_soc_hda_codec,snd_hda_intel,snd_hda_ext_core,snd_hda_codec,snd_sof_intel_hda_common,snd_hda_codec_realtek_lib,snd_soc_hdac_hda,snd_hda_codec_alc269,snd_sof_intel_hda,snd_hda_codec_intelhdmi
  cmdlinepart            16384  0
  videobuf2_v4l2         36864  1 uvcvideo
  ghash_clmulni_intel    12288  0
  btrtl                  32768  1 btusb
  snd_intel_dspcfg       45056  5 snd_soc_avs,snd_hda_intel,snd_sof,snd_sof_intel_hda_common,snd_sof_intel_hda_generic
  spi_nor               167936  0
  videobuf2_common       86016  4 videobuf2_vmalloc,videobuf2_v4l2,uvcvideo,videobuf2_memops
  aesni_intel            98304  5
  processor_thermal_device_pci_legacy    12288  0
  btintel                69632  1 btusb
  snd_intel_sdw_acpi     16384  2 snd_intel_dspcfg,snd_sof_intel_hda_generic
  rapl                   20480  0
  nls_iso8859_1          12288  1
  ee1004                 16384  0
  intel_rapl_msr         20480  0
  mei_pxp                16384  0
  mei_hdcp               28672  0
  mtd                    98304  3 spi_nor,cmdlinepart
  iwlmvm                897024  0
  videodev              364544  2 videobuf2_v4l2,uvcvideo
  processor_thermal_device    24576  1 processor_thermal_device_pci_legacy
  btbcm                  24576  1 btusb
  snd_hwdep              24576  1 snd_hda_codec
  mc                     81920  4 videodev,videobuf2_v4l2,uvcvideo,videobuf2_common
  intel_cstate           20480  0
  i915                 4837376  29
  btmtk                  36864  1 btusb
  mac80211             1851392  1 iwlmvm
  processor_thermal_wt_hint    16384  1 processor_thermal_device
  think_lmi              45056  0
  libarc4                12288  1 mac80211
  snd_soc_core          417792  7 snd_soc_avs,snd_soc_hda_codec,soundwire_intel,snd_sof,snd_soc_sdca,snd_sof_intel_hda_common,snd_soc_hdac_hda
  platform_temperature_control    20480  1 processor_thermal_device
  bluetooth            1032192  34 btrtl,btmtk,btintel,btbcm,bnep,btusb,rfcomm
  processor_thermal_soc_slider    16384  1 processor_thermal_device
  snd_compress           36864  2 snd_soc_avs,snd_soc_core
  drm_buddy              28672  1 i915
  processor_thermal_rfim    40960  1 processor_thermal_device
  ac97_bus               12288  1 snd_soc_core
  processor_thermal_rapl    16384  1 processor_thermal_device
  firmware_attributes_class    12288  1 think_lmi
  snd_pcm_dmaengine      20480  1 snd_soc_core
  ttm                   126976  1 i915
  i2c_i801               36864  0
  intel_rapl_common      53248  2 intel_rapl_msr,processor_thermal_rapl
  iwlwifi               647168  1 iwlmvm
  nxp_nci_i2c            16384  0
  snd_pcm               200704  14 snd_soc_avs,snd_hda_codec_hdmi,snd_hda_intel,snd_hda_codec,soundwire_intel,snd_sof,snd_soc_sdca,snd_sof_intel_hda_common,snd_compress,snd_sof_intel_hda_generic,snd_soc_core,snd_sof_utils,snd_hda_core,snd_pcm_dmaengine
  i2c_smbus              20480  1 i2c_i801
  processor_thermal_wt_req    12288  1 processor_thermal_device
  drm_display_helper    290816  1 i915
  spi_intel_pci          12288  0
  nxp_nci                12288  1 nxp_nci_i2c
  wmi_bmof               12288  0
  intel_wmi_thunderbolt    16384  0
  snd_ctl_led            24576  0
  processor_thermal_power_floor    12288  1 processor_thermal_device
  snd_timer              53248  3 snd_seq,snd_hrtimer,snd_pcm
  i2c_mux                12288  1 i2c_i801
  nci                    90112  2 nxp_nci,nxp_nci_i2c
  cfg80211             1462272  3 iwlmvm,iwlwifi,mac80211
  spi_intel              36864  1 spi_intel_pci
  cec                    98304  2 drm_display_helper,i915
  intel_pch_thermal      16384  0
  mei_me                 53248  2
  mei                   172032  5 mei_hdcp,mei_pxp,mei_me
  processor_thermal_mbox    12288  4 processor_thermal_power_floor,processor_thermal_wt_req,processor_thermal_rfim,processor_thermal_wt_hint
  rc_core                73728  1 cec
  thinkpad_acpi         163840  0
  nfc                   143360  2 nci,nxp_nci
  i2c_algo_bit           16384  1 i915
  intel_soc_dts_iosf     16384  1 processor_thermal_device_pci_legacy
  int3403_thermal        16384  0
  nvram                  20480  1 thinkpad_acpi
  int340x_thermal_zone    16384  2 int3403_thermal,processor_thermal_device
  int3400_thermal        24576  0
  acpi_thermal_rel       24576  1 int3400_thermal
  acpi_pad              184320  0
====
1:170c
  serio_raw              20480  0
2:111,112c
  soc_button_array       20480  0
  joydev                 32768  0
3:152c
  joydev                 32768  0
====1
1:171a
2:114c
3:154c
  serio_raw              20480  0
====1
1:176c
  lp                     28672  0
2:119c
3:159c
  lp                     32768  0
====
1:179,180c
  nfnetlink              20480  6 nft_compat,nf_conntrack_netlink,nf_tables,ip_set
  dmi_sysfs              24576  0
2:122,123c
  nfnetlink              20480  6 nft_compat,nf_conntrack_netlink,nf_tables,ip_set
  dmi_sysfs              20480  0
3:162,163c
  nfnetlink              20480  1
  dmi_sysfs              20480  0
====3
1:182c
2:125c
  x_tables               65536  8 xt_conntrack,nft_compat,xt_tcpudp,xt_addrtype,xt_nat,xt_set,ip_tables,xt_MASQUERADE
3:165c
  x_tables               65536  1 ip_tables
====
1:184,228c
  btrfs                2056192  0
  blake2b_generic        24576  0
  raid10                 77824  0
  raid456               196608  0
  async_raid6_recov      20480  1 raid456
  async_memcpy           16384  2 raid456,async_raid6_recov
  async_pq               20480  2 raid456,async_raid6_recov
  async_xor              16384  3 async_pq,raid456,async_raid6_recov
  async_tx               16384  5 async_pq,async_memcpy,async_xor,raid456,async_raid6_recov
  xor                    20480  2 async_xor,btrfs
  raid6_pq              126976  4 async_pq,btrfs,raid456,async_raid6_recov
  libcrc32c              12288  5 nf_conntrack,nf_nat,btrfs,nf_tables,raid456
  raid1                  61440  0
  raid0                  24576  0
  dm_mirror              24576  0
  dm_region_hash         24576  1 dm_mirror
  dm_log                 20480  2 dm_region_hash,dm_mirror
  hid_multitouch         36864  0
  crct10dif_pclmul       12288  1
  crc32_pclmul           12288  0
  hid_generic            12288  0
  polyval_clmulni        12288  0
  polyval_generic        12288  1 polyval_clmulni
  ghash_clmulni_intel    16384  0
  sha256_ssse3           32768  0
  psmouse               217088  0
  sha1_ssse3             32768  0
  video                  77824  4 dell_wmi,dell_laptop,xe,i915
  r8169                 118784  0
  intel_lpss_pci         28672  0
  xhci_pci               24576  0
  realtek                36864  1
  ahci                   49152  2
  intel_lpss             12288  1 intel_lpss_pci
  libahci                53248  1 ahci
  idma64                 20480  0
  xhci_pci_renesas       20480  1 xhci_pci
  i2c_hid_acpi           12288  0
  i2c_hid                40960  1 i2c_hid_acpi
  hid                   180224  4 i2c_hid,usbhid,hid_multitouch,hid_generic
  wmi                    28672  7 dell_wmi_sysman,video,dell_wmi,wmi_bmof,dell_smm_hwmon,dell_smbios,dell_wmi_descriptor
  pinctrl_tigerlake      28672  1
  aesni_intel           356352  10
  crypto_simd            16384  1 aesni_intel
  cryptd                 24576  3 crypto_simd,ghash_clmulni_intel
2:127,144c
  rtsx_usb_sdmmc         36864  0
  rtsx_usb               32768  2 rtsx_usb_sdmmc,rtsx_usb_ms
  usbhid                 77824  0
  hid_multitouch         36864  0
  hid_generic            12288  0
  nvme                   61440  2
  r8169                 139264  0
  ahci                   49152  0
  nvme_core             233472  3 nvme
  nvme_keyring           20480  1 nvme_core
  realtek                49152  1
  libahci                53248  1 ahci
  i2c_hid_acpi           12288  0
  nvme_auth              28672  1 nvme_core
  i2c_hid                40960  1 i2c_hid_acpi
  video                  77824  1 amdgpu
  wmi                    28672  1 video
  hid                   262144  4 i2c_hid,usbhid,hid_multitouch,hid_generic
3:167,188c
  ucsi_acpi              12288  0
  typec_ucsi             69632  1 ucsi_acpi
  typec                 118784  1 typec_ucsi
  nvme                   61440  2
  rtsx_pci_sdmmc         36864  0
  snd                   143360  22 snd_ctl_led,snd_hda_codec_generic,snd_seq,snd_seq_device,snd_hda_codec_hdmi,snd_hwdep,snd_hda_intel,snd_hda_codec,snd_sof,snd_soc_sdca,snd_timer,snd_hda_codec_realtek_lib,snd_compress,thinkpad_acpi,snd_hda_codec_alc269,snd_soc_core,snd_pcm,snd_rawmidi
  soundcore              16384  2 snd_ctl_led,snd
  nvme_core             233472  3 nvme
  video                  77824  2 thinkpad_acpi,i915
  intel_lpss_pci         28672  0
  nvme_keyring           20480  1 nvme_core
  psmouse               217088  0
  e1000e                360448  0
  intel_lpss             12288  1 intel_lpss_pci
  thunderbolt           540672  1 typec
  nvme_auth              28672  1 nvme_core
  rtsx_pci              143360  1 rtsx_pci_sdmmc
  idma64                 20480  0
  platform_profile       20480  2 thinkpad_acpi,processor_thermal_soc_slider
  sparse_keymap          12288  1 thinkpad_acpi
  wmi                    28672  4 video,intel_wmi_thunderbolt,wmi_bmof,think_lmi
  pinctrl_cannonlake     36864  3
```

### ¿cuales no están cargados pero están disponibles?¿ Qué pasa cuando el driver de un dispositivo no está disponible?

Si se quiere ver la seccion de módulos por categoría: 

```bash
~/Do/facu/actuales/priSem/SdeC/GITarreros/tp4 joaquin !1 ?2 > ls /lib/modules/$(uname -r)/kernel/
arch  block  crypto  drivers  fs  kernel  lib  mm  net  samples  sound  ubuntu  v4l2loopback  virt  zfs
```
Los módulos disponibles: 
```bash
~/Do/facu/actuales/priSem/SdeC/GITarreros/tp4 joaquin !1 ?2 > find /lib/modules/$(uname -r)/kernel/ -name "*.ko*" | wc -l
6474
```
Y los módulos cargados: 
```bash
~/Do/facu/actuales/priSem/SdeC/GITarreros/tp4 joaquin !1 ?2 > lsmod | wc -l
228
```
Cuando el driver de un dispositivo no está disponible, el SO no puede comunicarse con el hardware. Esto significa que la computadora no sabe qué funciones tiene ese componente ni cómo enviarle instrucciones. Por lo que el dispositivo no funcionará, o el SO lo marcará como sin reclamar. En caso de que se intente forzar el uso de un dispositivo o hardware sin su driver, puede generar errores en el kernel (kernel panic). 

### ¿Qué diferencia existe entre un módulo de kernel y un programa?

La diferencia principal es que un `módulo de kernel` se ejecuta dentro del "cerebro" del sistema operativo (espacio de kernel) con acceso total al hardware, mientras que un `programa común` se ejecuta en un entorno restringido y seguro (espacio de usuario) controlado por el kernel.
Un módulo de kernel se ejecuta en el espacio de kernel (Anillo 0), y por lo tanto tiene control absoluto sobre la memoria RAM, el procesador y los componentes. Un error acá congela todo el SO (Kernel panic). 
Un programa se ejecuta en el espacio de usuario. Su memoria está aislada y por lo tanto si el programa falla o se rompe, el SO simplemente lo cierra y la PC sigue funcionando normalmente. 

### ¿Cómo puedo ver la lista de llamadas al sistema que realiza un simple helloworld en c?

Para interceptar y listar llamadas al sistema (syscalls), se utiliza strace: 
```bash 
~/Do/f/ac/p/S/GITarreros/tp4/hello_checkinstall joaquin !1 ?3 > strace ./hello                  
execve("./hello", ["./hello"], 0x7ffdff9bec40 /* 55 vars */) = 0
brk(NULL)                               = 0x614c8e5cb000
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x76c96c94d000
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No existe el archivo o el directorio)
openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=121763, ...}) = 0
mmap(NULL, 121763, PROT_READ, MAP_PRIVATE, 3, 0) = 0x76c96c92f000
close(3)                                = 0
openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\220\243\2\0\0\0\0\0"..., 832) = 832
pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784
fstat(3, {st_mode=S_IFREG|0755, st_size=2125328, ...}) = 0
pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784
mmap(NULL, 2170256, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x76c96c600000
mmap(0x76c96c628000, 1605632, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x28000) = 0x76c96c628000
mmap(0x76c96c7b0000, 323584, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1b0000) = 0x76c96c7b0000
mmap(0x76c96c7ff000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1fe000) = 0x76c96c7ff000
mmap(0x76c96c805000, 52624, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x76c96c805000
close(3)                                = 0
mmap(NULL, 12288, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x76c96c92c000
arch_prctl(ARCH_SET_FS, 0x76c96c92c740) = 0
set_tid_address(0x76c96c92ca10)         = 89817
set_robust_list(0x76c96c92ca20, 24)     = 0
rseq(0x76c96c92d060, 0x20, 0, 0x53053053) = 0
mprotect(0x76c96c7ff000, 16384, PROT_READ) = 0
mprotect(0x614c89f55000, 4096, PROT_READ) = 0
mprotect(0x76c96c985000, 8192, PROT_READ) = 0
prlimit64(0, RLIMIT_STACK, NULL, {rlim_cur=8192*1024, rlim_max=RLIM64_INFINITY}) = 0
munmap(0x76c96c92f000, 121763)          = 0
fstat(1, {st_mode=S_IFCHR|0620, st_rdev=makedev(0x88, 0), ...}) = 0
getrandom("\xe1\x0b\x96\xb6\x20\x9f\x06\x8a", 8, GRND_NONBLOCK) = 8
brk(NULL)                               = 0x614c8e5cb000
brk(0x614c8e5ec000)                     = 0x614c8e5ec000
write(1, "\302\241Hola Mundo desde un paquete .d"..., 36¡Hola Mundo desde un paquete .deb!
) = 36
exit_group(0)                           = ?
+++ exited with 0 +++
```
Para tomar nota del algunas: 

**`execve()`**: Primera llamada. El SO la usa para cargar el archivo en la memoria y empezar a ejecutarlo. 

**`mmap()`** y **`mprotect()`**: El sistema reserva espacio en la memoria RAM para el programa y las librerias de C que necesita cargar (como libc que contiene la funcion printf).

**`write(1, "Hola Mundo..., 36)`**: printf formatea el texto y le pide al kernel (usando la syscall write) que envíe esos 36 caracteres a la salida estándar (1, que es la terminal).

**`exit_group(0)`**: El programa le avisa al kernel que terminó exitosamente (el 'return 0') para que libere la memoria. 

### ¿Qué es un segmentation fault? ¿Cómo lo maneja el kernel y como lo hace un programa?

Un segmentation fault es un error de acceso a la memoria. Ocurre cuando un programa intenta salirse de su espacio e interactuar con una porción de la memoria para la cual no tiene permisos. 
Algunas causas suelen ser por:
- Intentar leer o escribir en un puntero nulo (NULL pointer).
- Intentar acceder a memoria que ya fue liberada.
- Intentar escribir en una sección de memoria que es read only.
- Intentar acceder a memoria reservada exclusivamente para el kernel. 

El manejo del error es el siguiente: 
- **`Detección`**: Cuando el programa intenta el acceso ilegal, un chip en el procesador llamado `MMU` (Memory Management Unit) detecta la anomalía y dispara una interrupción por hardware.

**`Generación de la señal`**: El kernel toma el control inmediatamente, analiza qué proceso causó la interrupción y le envía una señal fatal específica: la señal `SIGSEGV` (Signal 11 - Segmentation Violation).

**`Ejecución`**: Si el programa no tiene un plan para esa señal (que es lo normal), el kernel termina el proceso (lo mata) instantáneamente para proteger al resto del sistema. Además, suele generar un archivo llamado `core dump` (un volcado de la memoria exacta que tenía el programa al momento de morir) para que el programador pueda depurar el error después. 




## Basándose en el artículo de Ars Technica y en el funcionamiento de los SO, se respondieron las siguientes preguntas:

### ¿Cuál fue la consecuencia principal del parche de Microsoft sobre GRUB en sistemas con arranque dual?

La consecuencia principal fue que bloqueó el acceso a las particiones de Linux, impidiendo que los usuarios pudieran iniciar su sistema operativo Linux en computadoras con arranque dual (Windows y Linux). Microsoft lanzó este parche en agosto de 2024 para actualizar la lista SBAT (Secure Boot Advanced Targeting) y revocar versiones antiguas y vulnerables del gestor de arranque GRUB (usado por la mayoría de las distribuciones de Linux). Aunque Microsoft aseguró que esta actualización no afectaría a los sistemas configurados con arranque dual, el parche se aplicó incorrectamente en muchos de ellos. Como resultado, al intentar iniciar Linux, los usuarios se encontraban con un error crítico (como "Something has gone seriously wrong: SBAT self-check failed: Security Policy Violation") y el sistema se detenía.

### ¿Qué implicancia tiene desactivar Secure Boot como solución a este problema?

La principal implicancia es una reducción significativa en la seguridad del sistema. Como solución temporal, los usuarios descubrieron que al entrar a la BIOS/UEFI de su computadora y apagar el "Secure Boot", Linux volvía a iniciar (ya que al apagarlo, el sistema deja de revisar la lista SBAT que bloqueaba a GRUB). Sin embargo, desactivar esta función deja a la computadora vulnerable ante bootkits y rootkits (malware extremadamente peligroso que se inyecta antes de que cargue el sistema operativo o el antivirus). Es decir, resuelves el problema de accesibilidad, pero sacrificas la barrera de seguridad que protege la integridad del arranque de tu equipo.

### ¿Cuál es el propósito principal del Secure Boot en el proceso de arranque?

El propósito principal de Secure Boot es garantizar que la computadora inicie utilizando únicamente software de confianza, protegiendo al equipo de código malicioso desde el momento en que se presiona el botón de encendido. 
Funciona creando una "cadena de confianza" mediante criptografía: 

1. Cuando se enciende la PC, el firmware (BIOS/UEFI) revisa la firma digital del gestor de arranque (como el de Windows o GRUB).

2. Si la firma es válida y pertenece a una lista de claves autorizadas guardada en la placa madre, le permite ejecutarse.

3. Luego, el gestor de arranque hace lo mismo con el núcleo (kernel) del sistema operativo, y así sucesivamente.

4. Si en algún momento un archivo de la cadena fue alterado (por ejemplo, por un virus que modificó el gestor de arranque para espiarte), la firma no coincidirá, el Secure Boot lo detectará como una violación de seguridad y detendrá el proceso de arranque para proteger los datos.




## Empaquetamiento con checkinstall


Se crea el directorio donde se realizará la experiencia:
```bash
~/Do/facu/actuales/priSem/SdeC/GITarreros/tp4 joaquin +3 !1 ?2 > mkdir hello_checkinstall                                            %
```
Se ingresa al directorio:
```bash
~/Do/facu/actuales/priSem/SdeC/GITarreros/tp4 joaquin +3 !1 ?2 > cd hello_checkinstall                                               %
```
Se lista el contenido del directorio:
```bash
~/Do/f/ac/p/S/GITarreros/tp4/hello_checkinstall joaquin +3 !1 ?2 > ls                                                                %
```
Mediante nano, se crea el archivo .c:
```bash
~/Do/f/ac/p/S/GITarreros/tp4/hello_checkinstall joaquin +3 !1 ?2 > nano hello.c                                                      %
```
Se diseña el Makefile para automatizar la compilación e instalación:
```bash
~/Do/f/ac/p/S/GITarreros/tp4/hello_checkinstall joaquin +3 !1 ?3 > nano Makefile                                                 10s %
```
Se corrobora que efectivamente estén creados:
```bash
~/Do/f/ac/p/S/GITarreros/tp4/hello_checkinstall joaquin +3 !1 ?3 > ls                                                            18s %
hello.c  Makefile
```

Se ejecuta 'make'. El sistema lee el script del Makefile e invoca a gcc para traducir el código fuente en un binario ejecutable 'hello'
```bash
~/Do/f/ac/p/S/GITarreros/tp4/hello_checkinstall joaquin +3 !1 ?3 > make                                                              %
gcc hello.c -o hello
```
Se ejecuta 'sudo checkinstall'. Esta herramienta intercepta el proceso de instalación del Makefile, genera un paquete Debian y lo instala a través de 'dpkg'
```bash
~/Do/f/ac/p/S/GITarreros/tp4/hello_checkinstall joaquin +3 !1 ?3 > sudo checkinstall                                                 %

checkinstall 1.6.3, Copyright 2010 Felipe Eduardo Sanchez Diaz Duran
           Este software es distribuído de acuerdo a la GNU GPL


The package documentation directory ./doc-pak does not exist. 
Should I create a default set of package docs?  [y]: y

Preparando la documentación del paquete...OK

*** No known documentation files were found. The new package 
*** won't include a documentation directory.

Por favor escribe una descripción para el paquete.
Termina tu descripcion con una linea vacia o con EOF.
>> 

*****************************************
**** Debian package creation selected ***
*****************************************

*** Warning: The package name "hello_checkinstall" contains illegal
*** Warning: characters. dpkg might not like that so I changed
*** Warning: them to dashes.

Este paquete será creado de acuerdo a estos valores:

0 -  Maintainer: [ root@joaquin-Inspiron-3501 ]
1 -  Summary: [ Package created with checkinstall 1.6.3 ]
2 -  Name:    [ hello-checkinstall ]
3 -  Version: [ 20260601 ]
4 -  Release: [ 1 ]
5 -  License: [ GPL ]
6 -  Group:   [ checkinstall ]
7 -  Architecture: [ amd64 ]
8 -  Source location: [ hello_checkinstall ]
9 -  Alternate source location: [  ]
10 - Requires: [  ]
11 - Recommends: [  ]
12 - Suggests: [  ]
13 - Provides: [ hello-checkinstall ]
14 - Conflicts: [  ]
15 - Replaces: [  ]
16 - Prerequires: [  ]

Introduce un número para cambiar algún dato u oprime ENTER para continuar:

Installing with make install...

====================== Resultados de la instalación  =====================
mkdir -p /usr/local/bin
cp hello /usr/local/bin/

========================== Instalación exitosa ===========================

Copiando los archivos al directorio temporal...OK

Stripping ELF binaries and libraries...OK

Comprimiendo las páginas de manual...OK

Creando la lista de archivos...OK

Creando el paquete Debian...OK

Instalando el paquete Debian...OK

Borrando directorios temporales...OK

Borrando el directorio temporal...OK


**********************************************************************

 Done. The new package has been installed and saved to

 /home/joaquin/Documentos/facu/actuales/priSem/SdeC/GITarreros/tp4/hello_checkinstall/hello-checkinstall_20260601-1_amd64.deb

 You can remove it from your system anytime using: 

      dpkg -r hello-checkinstall

**********************************************************************
```

### Strace

Una vez instalado el binario, se ejecuta 'strace hello'. Esto permite realizar un trazado completo de la interacción entre el programa (Espacio de usuario) y el kernel(Espacio de kernel)
```bash
~/Do/f/ac/p/S/GITarreros/tp4/hello_checkinstall joaquin +3 !1 ?4 > strace hello           
execve("/usr/local/bin/hello", ["hello"], 0x7ffec3becb40 /* 55 vars */) = 0
brk(NULL)                               = 0x643281d05000
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x75c55fcd6000
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No existe el archivo o el directorio)
openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=121643, ...}) = 0
mmap(NULL, 121643, PROT_READ, MAP_PRIVATE, 3, 0) = 0x75c55fcb8000
close(3)                                = 0
openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\220\243\2\0\0\0\0\0"..., 832) = 832
pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784
fstat(3, {st_mode=S_IFREG|0755, st_size=2125328, ...}) = 0
pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784
mmap(NULL, 2170256, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x75c55fa00000
mmap(0x75c55fa28000, 1605632, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x28000) = 0x75c55fa28000
mmap(0x75c55fbb0000, 323584, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1b0000) = 0x75c55fbb0000
mmap(0x75c55fbff000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1fe000) = 0x75c55fbff000
mmap(0x75c55fc05000, 52624, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x75c55fc05000
close(3)                                = 0
mmap(NULL, 12288, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x75c55fcb5000
arch_prctl(ARCH_SET_FS, 0x75c55fcb5740) = 0
set_tid_address(0x75c55fcb5a10)         = 18070
set_robust_list(0x75c55fcb5a20, 24)     = 0
rseq(0x75c55fcb6060, 0x20, 0, 0x53053053) = 0
mprotect(0x75c55fbff000, 16384, PROT_READ) = 0
mprotect(0x643276c06000, 4096, PROT_READ) = 0
mprotect(0x75c55fd0e000, 8192, PROT_READ) = 0
prlimit64(0, RLIMIT_STACK, NULL, {rlim_cur=8192*1024, rlim_max=RLIM64_INFINITY}) = 0
munmap(0x75c55fcb8000, 121643)          = 0
fstat(1, {st_mode=S_IFCHR|0620, st_rdev=makedev(0x88, 0), ...}) = 0
getrandom("\xd1\x62\xab\xcf\x25\x49\x1d\x05", 8, GRND_NONBLOCK) = 8
brk(NULL)                               = 0x643281d05000
brk(0x643281d26000)                     = 0x643281d26000
write(1, "\302\241Hola Mundo desde un paquete .d"..., 36¡Hola Mundo desde un paquete .deb!
) = 36
exit_group(0)                           = ?
+++ exited with 0 +++
```
