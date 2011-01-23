# -*- RPM-SPEC -*-
%define name    flickcurl
%define version 1.20
%define release 1

%define major 0
%define libname libflickcurl0
%define devname libflickcurl-devel

Summary:	Flickcurl C library for the Flickr API
Name:		%name
Version:	%version
Release:	%release
Prefix:         %{_prefix}
License:	LGPL 2.1 / ASL 2.0
Group:		System/Libraries
Source0:	http://download.dajobe.org/flickcurl/%{name}-%{version}.tar.gz
URL:		http://librdf.org/flickcurl/
BuildRequires:	curl-devel >= 7.10.0, libxml2-devel >= 2.6.8, raptor-devel >= 1.4.16
Buildroot:      %{_tmppath}/%{name}-%{version}-%{release}-root

%description
Flickcurl is a C library for the Flickr API, handling creating the
requests, signing, token management, calling the API, marshalling request
parameters and decoding responses. It uses libcurl to call the REST
web service and libxml2 to manipulate the XML responses. The current
version supports the majority of the API (see Flickcurl API coverage)
including the functions for photo uploading, browsing, searching, adding
and editing comments, groups, notes, photosets, categories, tags and photo
metadata. It also includes a program flickrdf to turn photo metadata,
tags and machine tags into RDF descriptions of photso and tags.

This package contains utility programs that use the %{name} library.


%package -n %libname
Summary:	C library for the Flickr API
Group:		System/Libraries

%description -n %libname
Flickcurl is a C library for the Flickr API, handling creating the
requests, signing, token management, calling the API, marshalling request
parameters and decoding responses. It uses libcurl to call the REST
web service and libxml2 to manipulate the XML responses. The current
version supports the majority of the API (see Flickcurl API coverage)
including the functions for photo uploading, browsing, searching, adding
and editing comments, groups, notes, photosets, categories, tags and photo
metadata. It also includes a program flickrdf to turn photo metadata,
tags and machine tags into RDF descriptions of photso and tags.

%package -n %devname
Summary:	Development files for %libname
Group:		System/Libraries
Requires:	%{libname} = %{version}
Provides:	%name-devel = %version-%release, lib%{name}-devel = %version-%release

%description -n %devname
This package contains the developement files for the %{name} library.

%prep
%setup -q

%build
%configure

%{__make}

%install
rm -fr %{buildroot}

%makeinstall

%clean
rm -fr %{buildroot}

%post -n %{libname} -p /sbin/ldconfig

%postun -n %{libname} -p /sbin/ldconfig

%files
%doc LICENSE-2.0.txt LICENSE.html AUTHORS COPYING COPYING.LIB
%doc NEWS NEWS.html README README.html ChangeLog coverage.html
%{_bindir}/flickcurl
%{_bindir}/flickrdf

%{_mandir}/man1/flickcurl.1.*
%{_mandir}/man1/flickrdf.1.*

%files -n %libname
%{_libdir}/lib%{name}.so.%{major}*

%files -n %devname
%doc NOTICE
%{_bindir}/flickcurl-config

%{_libdir}/lib%{name}.a
%{_libdir}/lib%{name}.la
%{_libdir}/lib%{name}.so
%{_libdir}/pkgconfig/%{name}.pc

%{_includedir}/flickcurl.h

%{_mandir}/man1/flickcurl-config.1.*

%changelog
* Thu Dec 21 2007  Dave Beckett <dave@dajobe.org>
- Fedora 7 RPM packaging
