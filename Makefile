#############################################################################
# Makefile for building: ethmite
# Generated by qmake (3.0) (Qt 5.5.0)
# Project:  ethmite.pro
# Template: app
# Command: D:/usr/qt/5.5/mingw492_32/bin/qmake.exe -o Makefile ethmite.pro
#############################################################################

MAKEFILE      = Makefile

first: release
install: release-install
uninstall: release-uninstall
QMAKE         = D:/usr/qt/5.5/mingw492_32/bin/qmake.exe
DEL_FILE      = rm -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
COPY          = cp -f
COPY_FILE     = cp -f
COPY_DIR      = cp -f -R
INSTALL_FILE  = cp -f
INSTALL_PROGRAM = cp -f
INSTALL_DIR   = cp -f -R
DEL_FILE      = rm -f
SYMLINK       = $(QMAKE) -install ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
SUBTARGETS    =  \
		release \
		debug


release: FORCE
	$(MAKE) -f $(MAKEFILE).Release
release-make_first: FORCE
	$(MAKE) -f $(MAKEFILE).Release 
release-all: FORCE
	$(MAKE) -f $(MAKEFILE).Release all
release-clean: FORCE
	$(MAKE) -f $(MAKEFILE).Release clean
release-distclean: FORCE
	$(MAKE) -f $(MAKEFILE).Release distclean
release-install: FORCE
	$(MAKE) -f $(MAKEFILE).Release install
release-uninstall: FORCE
	$(MAKE) -f $(MAKEFILE).Release uninstall
debug: FORCE
	$(MAKE) -f $(MAKEFILE).Debug
debug-make_first: FORCE
	$(MAKE) -f $(MAKEFILE).Debug 
debug-all: FORCE
	$(MAKE) -f $(MAKEFILE).Debug all
debug-clean: FORCE
	$(MAKE) -f $(MAKEFILE).Debug clean
debug-distclean: FORCE
	$(MAKE) -f $(MAKEFILE).Debug distclean
debug-install: FORCE
	$(MAKE) -f $(MAKEFILE).Debug install
debug-uninstall: FORCE
	$(MAKE) -f $(MAKEFILE).Debug uninstall

Makefile: ethmite.pro ../../../usr/qt/5.5/mingw492_32/mkspecs/win32-g++/qmake.conf ../../../usr/qt/5.5/mingw492_32/mkspecs/features/spec_pre.prf \
		../../../usr/qt/5.5/mingw492_32/mkspecs/qdevice.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/features/device_config.prf \
		../../../usr/qt/5.5/mingw492_32/mkspecs/qconfig.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_3dcore.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_3dcore_private.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_3dinput.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_3dinput_private.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_3dquick.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_3dquick_private.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_3dquickrenderer.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_3dquickrenderer_private.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_3drenderer.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_3drenderer_private.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_axbase.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_axbase_private.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_axcontainer.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_axcontainer_private.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_axserver.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_axserver_private.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_bluetooth.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_bluetooth_private.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_bootstrap_private.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_clucene_private.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_concurrent.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_concurrent_private.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_core.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_core_private.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_dbus.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_dbus_private.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_declarative.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_declarative_private.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_designer.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_designer_private.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_designercomponents_private.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_enginio.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_enginio_private.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_gui.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_gui_private.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_help.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_help_private.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_location.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_location_private.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_multimedia.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_multimedia_private.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_multimediawidgets.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_multimediawidgets_private.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_network.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_network_private.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_nfc.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_nfc_private.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_opengl.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_opengl_private.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_openglextensions.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_openglextensions_private.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_platformsupport_private.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_positioning.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_positioning_private.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_printsupport.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_printsupport_private.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_qml.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_qml_private.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_qmldevtools_private.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_qmltest.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_qmltest_private.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_qtmultimediaquicktools_private.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_quick.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_quick_private.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_quickparticles_private.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_quickwidgets.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_quickwidgets_private.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_script.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_script_private.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_scripttools.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_scripttools_private.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_sensors.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_sensors_private.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_serialport.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_serialport_private.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_sql.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_sql_private.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_svg.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_svg_private.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_testlib.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_testlib_private.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_uiplugin.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_uitools.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_uitools_private.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_webchannel.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_webchannel_private.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_webkit.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_webkit_private.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_webkitwidgets.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_webkitwidgets_private.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_websockets.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_websockets_private.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_widgets.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_widgets_private.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_winextras.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_winextras_private.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_xml.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_xml_private.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_xmlpatterns.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_xmlpatterns_private.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/features/qt_functions.prf \
		../../../usr/qt/5.5/mingw492_32/mkspecs/features/qt_config.prf \
		../../../usr/qt/5.5/mingw492_32/mkspecs/features/win32/qt_config.prf \
		../../../usr/qt/5.5/mingw492_32/mkspecs/win32-g++/qmake.conf \
		../../../usr/qt/5.5/mingw492_32/mkspecs/features/spec_post.prf \
		../../../usr/qt/5.5/mingw492_32/mkspecs/features/exclusive_builds.prf \
		../../../usr/qt/5.5/mingw492_32/mkspecs/features/default_pre.prf \
		../../../usr/qt/5.5/mingw492_32/mkspecs/features/win32/default_pre.prf \
		deployment.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/features/resolve_config.prf \
		../../../usr/qt/5.5/mingw492_32/mkspecs/features/exclusive_builds_post.prf \
		../../../usr/qt/5.5/mingw492_32/mkspecs/features/default_post.prf \
		../../../usr/qt/5.5/mingw492_32/mkspecs/features/qwtconfig.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/features/qwtfunctions.pri \
		../../../usr/qt/5.5/mingw492_32/mkspecs/features/qwt.prf \
		../../../usr/qt/5.5/mingw492_32/mkspecs/features/win32/rtti.prf \
		../../../usr/qt/5.5/mingw492_32/mkspecs/features/precompile_header.prf \
		../../../usr/qt/5.5/mingw492_32/mkspecs/features/warn_on.prf \
		../../../usr/qt/5.5/mingw492_32/mkspecs/features/qt.prf \
		../../../usr/qt/5.5/mingw492_32/mkspecs/features/resources.prf \
		../../../usr/qt/5.5/mingw492_32/mkspecs/features/moc.prf \
		../../../usr/qt/5.5/mingw492_32/mkspecs/features/win32/opengl.prf \
		../../../usr/qt/5.5/mingw492_32/mkspecs/features/uic.prf \
		../../../usr/qt/5.5/mingw492_32/mkspecs/features/win32/windows.prf \
		../../../usr/qt/5.5/mingw492_32/mkspecs/features/testcase_targets.prf \
		../../../usr/qt/5.5/mingw492_32/mkspecs/features/exceptions.prf \
		../../../usr/qt/5.5/mingw492_32/mkspecs/features/yacc.prf \
		../../../usr/qt/5.5/mingw492_32/mkspecs/features/lex.prf \
		ethmite.pro \
		D:/usr/qt/5.5/mingw492_32/lib/qtmain.prl \
		D:/usr/qt/5.5/mingw492_32/lib/Qt5QuickWidgets.prl \
		D:/usr/qt/5.5/mingw492_32/lib/Qt5Quick.prl \
		D:/usr/qt/5.5/mingw492_32/lib/Qt5Declarative.prl \
		D:/usr/qt/5.5/mingw492_32/lib/Qt5Svg.prl \
		D:/usr/qt/5.5/mingw492_32/lib/Qt5Widgets.prl \
		D:/usr/qt/5.5/mingw492_32/lib/Qt5Gui.prl \
		D:/usr/qt/5.5/mingw492_32/lib/Qt5Qml.prl \
		D:/usr/qt/5.5/mingw492_32/lib/Qt5Network.prl \
		D:/usr/qt/5.5/mingw492_32/lib/Qt5Script.prl \
		D:/usr/qt/5.5/mingw492_32/lib/Qt5Core.prl
	$(QMAKE) -o Makefile ethmite.pro
../../../usr/qt/5.5/mingw492_32/mkspecs/features/spec_pre.prf:
../../../usr/qt/5.5/mingw492_32/mkspecs/qdevice.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/features/device_config.prf:
../../../usr/qt/5.5/mingw492_32/mkspecs/qconfig.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_3dcore.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_3dcore_private.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_3dinput.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_3dinput_private.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_3dquick.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_3dquick_private.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_3dquickrenderer.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_3dquickrenderer_private.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_3drenderer.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_3drenderer_private.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_axbase.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_axbase_private.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_axcontainer.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_axcontainer_private.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_axserver.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_axserver_private.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_bluetooth.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_bluetooth_private.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_bootstrap_private.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_clucene_private.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_concurrent.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_concurrent_private.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_core.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_core_private.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_dbus.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_dbus_private.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_declarative.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_declarative_private.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_designer.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_designer_private.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_designercomponents_private.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_enginio.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_enginio_private.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_gui.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_gui_private.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_help.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_help_private.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_location.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_location_private.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_multimedia.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_multimedia_private.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_multimediawidgets.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_multimediawidgets_private.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_network.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_network_private.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_nfc.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_nfc_private.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_opengl.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_opengl_private.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_openglextensions.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_openglextensions_private.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_platformsupport_private.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_positioning.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_positioning_private.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_printsupport.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_printsupport_private.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_qml.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_qml_private.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_qmldevtools_private.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_qmltest.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_qmltest_private.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_qtmultimediaquicktools_private.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_quick.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_quick_private.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_quickparticles_private.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_quickwidgets.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_quickwidgets_private.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_script.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_script_private.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_scripttools.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_scripttools_private.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_sensors.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_sensors_private.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_serialport.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_serialport_private.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_sql.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_sql_private.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_svg.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_svg_private.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_testlib.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_testlib_private.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_uiplugin.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_uitools.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_uitools_private.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_webchannel.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_webchannel_private.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_webkit.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_webkit_private.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_webkitwidgets.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_webkitwidgets_private.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_websockets.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_websockets_private.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_widgets.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_widgets_private.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_winextras.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_winextras_private.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_xml.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_xml_private.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_xmlpatterns.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/modules/qt_lib_xmlpatterns_private.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/features/qt_functions.prf:
../../../usr/qt/5.5/mingw492_32/mkspecs/features/qt_config.prf:
../../../usr/qt/5.5/mingw492_32/mkspecs/features/win32/qt_config.prf:
../../../usr/qt/5.5/mingw492_32/mkspecs/win32-g++/qmake.conf:
../../../usr/qt/5.5/mingw492_32/mkspecs/features/spec_post.prf:
../../../usr/qt/5.5/mingw492_32/mkspecs/features/exclusive_builds.prf:
../../../usr/qt/5.5/mingw492_32/mkspecs/features/default_pre.prf:
../../../usr/qt/5.5/mingw492_32/mkspecs/features/win32/default_pre.prf:
deployment.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/features/resolve_config.prf:
../../../usr/qt/5.5/mingw492_32/mkspecs/features/exclusive_builds_post.prf:
../../../usr/qt/5.5/mingw492_32/mkspecs/features/default_post.prf:
../../../usr/qt/5.5/mingw492_32/mkspecs/features/qwtconfig.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/features/qwtfunctions.pri:
../../../usr/qt/5.5/mingw492_32/mkspecs/features/qwt.prf:
../../../usr/qt/5.5/mingw492_32/mkspecs/features/win32/rtti.prf:
../../../usr/qt/5.5/mingw492_32/mkspecs/features/precompile_header.prf:
../../../usr/qt/5.5/mingw492_32/mkspecs/features/warn_on.prf:
../../../usr/qt/5.5/mingw492_32/mkspecs/features/qt.prf:
../../../usr/qt/5.5/mingw492_32/mkspecs/features/resources.prf:
../../../usr/qt/5.5/mingw492_32/mkspecs/features/moc.prf:
../../../usr/qt/5.5/mingw492_32/mkspecs/features/win32/opengl.prf:
../../../usr/qt/5.5/mingw492_32/mkspecs/features/uic.prf:
../../../usr/qt/5.5/mingw492_32/mkspecs/features/win32/windows.prf:
../../../usr/qt/5.5/mingw492_32/mkspecs/features/testcase_targets.prf:
../../../usr/qt/5.5/mingw492_32/mkspecs/features/exceptions.prf:
../../../usr/qt/5.5/mingw492_32/mkspecs/features/yacc.prf:
../../../usr/qt/5.5/mingw492_32/mkspecs/features/lex.prf:
ethmite.pro:
D:/usr/qt/5.5/mingw492_32/lib/qtmain.prl:
D:/usr/qt/5.5/mingw492_32/lib/Qt5QuickWidgets.prl:
D:/usr/qt/5.5/mingw492_32/lib/Qt5Quick.prl:
D:/usr/qt/5.5/mingw492_32/lib/Qt5Declarative.prl:
D:/usr/qt/5.5/mingw492_32/lib/Qt5Svg.prl:
D:/usr/qt/5.5/mingw492_32/lib/Qt5Widgets.prl:
D:/usr/qt/5.5/mingw492_32/lib/Qt5Gui.prl:
D:/usr/qt/5.5/mingw492_32/lib/Qt5Qml.prl:
D:/usr/qt/5.5/mingw492_32/lib/Qt5Network.prl:
D:/usr/qt/5.5/mingw492_32/lib/Qt5Script.prl:
D:/usr/qt/5.5/mingw492_32/lib/Qt5Core.prl:
qmake: FORCE
	@$(QMAKE) -o Makefile ethmite.pro

qmake_all: FORCE

make_first: release-make_first debug-make_first  FORCE
all: release-all debug-all  FORCE
clean: release-clean debug-clean  FORCE
distclean: release-distclean debug-distclean  FORCE
	-$(DEL_FILE) Makefile

release-mocclean:
	$(MAKE) -f $(MAKEFILE).Release mocclean
debug-mocclean:
	$(MAKE) -f $(MAKEFILE).Debug mocclean
mocclean: release-mocclean debug-mocclean

release-mocables:
	$(MAKE) -f $(MAKEFILE).Release mocables
debug-mocables:
	$(MAKE) -f $(MAKEFILE).Debug mocables
mocables: release-mocables debug-mocables

check: first
FORCE:

$(MAKEFILE).Release: Makefile
$(MAKEFILE).Debug: Makefile
