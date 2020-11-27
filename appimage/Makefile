builddir=appimage_build
appdir=$(builddir)/AppDir
appimage=*.AppImage
linuxdeployname=linuxdeploy-x86_64.AppImage
linuxdeploy=$(builddir)/$(linuxdeployname)
url="https://github.com/linuxdeploy/linuxdeploy/releases/download/continuous/$(linuxdeployname)"

all: $(linuxdeploy) | $(builddir)
	-$(RM) $(appimage)
	-$(RM) -r $(appdir)
	cd $(builddir) && conan install ../.. --build=missing
	cd $(builddir) && cmake ../.. -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=Release
	$(MAKE) -C $(builddir) install DESTDIR=AppDir
	$(linuxdeploy) --appdir $(appdir) \
		-i rtype.png -d r-type_client.desktop --output appimage

$(linuxdeploy): | $(builddir)
	cd $(builddir) && wget $(url)
	chmod u+x $@

$(builddir):
	mkdir -p $@

clean:
	$(RM) -rf $(builddir)

fclean: clean
	$(RM) -rf $(appimage)

.PHONY: all clean fclean
