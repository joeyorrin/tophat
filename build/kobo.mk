KOBO_MENU_SOURCES = \
	$(SRC)/Version.cpp \
	$(SRC)/Formatter/HexColor.cpp \
	$(SRC)/Hardware/CPU.cpp \
	$(SRC)/Hardware/DisplayDPI.cpp \
	$(SRC)/Hardware/RotateDisplay.cpp \
	$(SRC)/Screen/Layout.cpp \
	$(SRC)/Screen/TerminalWindow.cpp \
	$(SRC)/Look/TerminalLook.cpp \
	$(SRC)/Look/DialogLook.cpp \
	$(SRC)/Look/IconLook.cpp \
	$(SRC)/Look/ButtonLook.cpp \
	$(SRC)/Gauge/LogoView.cpp \
	$(SRC)/Dialogs/DialogSettings.cpp \
	$(SRC)/Dialogs/WidgetDialog.cpp \
	$(SRC)/Dialogs/HelpDialog.cpp \
	$(SRC)/Dialogs/Message.cpp \
	$(SRC)/Dialogs/TextEntry.cpp \
	$(SRC)/Dialogs/KnobTextEntry.cpp \
	$(SRC)/Dialogs/TouchTextEntry.cpp \
	$(SRC)/Dialogs/SimulatorPromptWindow.cpp \
	$(TEST_SRC_DIR)/Fonts.cpp \
	$(TEST_SRC_DIR)/FakeLanguage.cpp \
	$(SRC)/Kobo/WPASupplicant.cpp \
	$(SRC)/Kobo/System.cpp \
	$(SRC)/Kobo/NetworkDialog.cpp \
	$(SRC)/Kobo/WPASupplicant.cpp \
	$(SRC)/Kobo/WifiDialog.cpp \
	$(SRC)/Kobo/FakeSymbols.cpp \
	$(SRC)/Kobo/KoboMenu.cpp
KOBO_MENU_LDADD = $(FAKE_LIBS)
KOBO_MENU_DEPENDS = WIDGET FORM SCREEN EVENT RESOURCE ASYNC OS THREAD MATH UTIL
KOBO_MENU_STRIP = y

$(eval $(call link-program,KoboMenu,KOBO_MENU))

ifeq ($(TARGET),UNIX)
OPTIONAL_OUTPUTS += $(KOBO_MENU_BIN)
endif

ifeq ($(TARGET_IS_KOBO),y)

KOBO_POWER_OFF_SOURCES = \
	$(TEST_SRC_DIR)/Fonts.cpp \
	$(SRC)/Hardware/RotateDisplay.cpp \
	$(SRC)/Logger/FlightParser.cpp \
	$(SRC)/Renderer/FlightListRenderer.cpp \
	$(SRC)/FlightInfo.cpp \
	$(SRC)/Thread/Mutex.cpp \
	$(SRC)/Kobo/PowerOff.cpp
KOBO_POWER_OFF_LDADD = $(FAKE_LIBS)
KOBO_POWER_OFF_DEPENDS = SCREEN RESOURCE IO OS UTIL TIME
KOBO_POWER_OFF_STRIP = y
$(eval $(call link-program,PowerOff,KOBO_POWER_OFF))
OPTIONAL_OUTPUTS += $(KOBO_POWER_OFF_BIN)

BITSTREAM_VERA_DIR ?= $(shell \
if [ -d /usr/share/fonts/truetype/ttf-bitstream-vera ]; then \
	echo /usr/share/fonts/truetype/ttf-bitstream-vera; \
elif [ -d /usr/share/fonts/bitstream-vera ]; then \
	echo /usr/share/fonts/bitstream-vera; \
fi)
BITSTREAM_VERA_NAMES = Vera VeraBd VeraIt VeraBI VeraMono
BITSTREAM_VERA_FILES = $(patsubst %,$(BITSTREAM_VERA_DIR)/%.ttf,$(BITSTREAM_VERA_NAMES))

# /mnt/onboard/.kobo/KoboRoot.tgz is a file that is picked up by
# /etc/init.d/rcS, extracted to / on each boot; we can use it to
# install XCSoar/TopHat
$(TARGET_OUTPUT_DIR)/KoboRoot.tgz: $(XCSOAR_BIN) \
	$(KOBO_MENU_BIN) $(KOBO_POWER_OFF_BIN) \
	$(BITSTREAM_VERA_FILES) \
	$(topdir)/kobo/rcS.tophat \
	$(topdir)/kobo/inittab $(topdir)/kobo/rcS $(topdir)/kobo/inetd.conf
	@$(NQ)echo "  TAR     $@"
	$(Q)rm -rf $(@D)/KoboRoot
	$(Q)install -m 0755 -d $(@D)/KoboRoot/etc $(@D)/KoboRoot/opt/tophat/bin $(@D)/KoboRoot/opt/tophat/share/fonts
	$(Q)install -m 0755 $(XCSOAR_BIN) $(KOBO_MENU_BIN) $(KOBO_POWER_OFF_BIN) $(topdir)/kobo/rcS $(@D)/KoboRoot/opt/tophat/bin
	$(Q)install -m 0644 $(topdir)/kobo/inittab $(@D)/KoboRoot/etc
	$(Q)install -m 0644 $(topdir)/kobo/inetd.conf $(@D)/KoboRoot/etc
	$(Q)install -m 0755 -d $(@D)/KoboRoot/etc/init.d
	$(Q)install -m 0755 $(topdir)/kobo/rcS.tophat $(@D)/KoboRoot/etc/init.d
	$(Q)install -m 0644 $(BITSTREAM_VERA_FILES) $(@D)/KoboRoot/opt/tophat/share/fonts
	$(Q)fakeroot tar czfC $@ $(@D)/KoboRoot .

endif
