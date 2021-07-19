#!/bin/bash
cat << EOF >> misc/mk/config.mk
ifneq (,\$(findstring \$(POK_PATH)/kernel, \$(PWD)))
 ifneq (,\$(AFLGCC))
  override CC_$ARCH=\$(AFLGCC)
 endif
endif
EOF
