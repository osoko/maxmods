' Copyright (c) 2009 Bruce A Henderson
' 
' Permission is hereby granted, free of charge, to any person obtaining a copy
' of this software and associated documentation files (the "Software"), to deal
' in the Software without restriction, including without limitation the rights
' to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
' copies of the Software, and to permit persons to whom the Software is
' furnished to do so, subject to the following conditions:
' 
' The above copyright notice and this permission notice shall be included in
' all copies or substantial portions of the Software.
' 
' THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
' IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
' FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
' AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
' LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
' OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
' THE SOFTWARE.
'
SuperStrict

Import BRL.Blitz
Import Pub.ZLib
Import Pub.Libjpeg
Import Pub.Libpng
Import BaH.expat
Import BaH.libcurl

Import "../../pub.mod/libjpeg.mod/*.h"
Import "../libcurl.mod/src/include/*.h"
Import "../expat.mod/src/*.h"

Import "gdal/proj/src/*.h"

Import "gdal/ogr/*.h"

Import "gdal/port/*.h"

Import "gdal/port/cpl_conv.cpp"
'Import "gdal/port/xmlreformat.cpp"
Import "gdal/port/cpl_csv.cpp"
Import "gdal/port/cpl_error.cpp"
Import "gdal/port/cpl_findfile.cpp"
Import "gdal/port/cpl_getexecpath.cpp"
Import "gdal/port/cpl_hash_set.cpp"
Import "gdal/port/cpl_http.cpp"
Import "gdal/port/cpl_list.cpp"
Import "gdal/port/cpl_minixml.cpp"
Import "gdal/port/cpl_minizip_ioapi.cpp"
Import "gdal/port/cpl_minizip_unzip.cpp"
Import "gdal/port/cpl_multiproc.cpp"
'Import "gdal/port/cpl_odbc.cpp"
Import "gdal/port/cpl_path.cpp"
Import "gdal/port/cpl_quad_tree.cpp"
Import "gdal/port/cpl_recode_stub.cpp"
Import "gdal/port/cpl_string.cpp"
Import "gdal/port/cpl_strtod.cpp"
Import "gdal/port/cpl_vsi_mem.cpp"
Import "gdal/port/cpl_vsil_gzip.cpp"
'Import "gdal/port/cpl_vsil_simple.cpp"
Import "gdal/port/cpl_vsil_unix_stdio_64.cpp"
Import "gdal/port/cpl_vsil_win32.cpp"
Import "gdal/port/cpl_vsil.cpp"
Import "gdal/port/cpl_vsisimple.cpp"
'Import "gdal/port/cpl_win32ce_api.cpp"
Import "gdal/port/cplgetsymbol.cpp"
Import "gdal/port/cplkeywordparser.cpp"
Import "gdal/port/cplstring.cpp"

Import "gdal/gcore/*.h"

Import "gdal/gcore/gdal_misc.cpp"
Import "gdal/gcore/rasterio.cpp"
Import "gdal/gcore/gdal_rat.cpp"
Import "gdal/gcore/gdal_rpcimdio.cpp"
Import "gdal/gcore/gdalallvalidmaskband.cpp"
Import "gdal/gcore/gdalcolortable.cpp"
Import "gdal/gcore/gdaldataset.cpp"
Import "gdal/gcore/gdaldefaultoverviews.cpp"
Import "gdal/gcore/gdaldriver.cpp"
Import "gdal/gcore/gdaldrivermanager.cpp"
Import "gdal/gcore/gdalgmlcoverage.cpp"
Import "gdal/gcore/gdaljp2box.cpp"
Import "gdal/gcore/gdaljp2metadata.cpp"
Import "gdal/gcore/gdalmajorobject.cpp"
Import "gdal/gcore/gdalmultidomainmetadata.cpp"
Import "gdal/gcore/gdalnodatamaskband.cpp"
Import "gdal/gcore/gdalnodatavaluesmaskband.cpp"
Import "gdal/gcore/gdalopeninfo.cpp"
Import "gdal/gcore/gdalpamdataset.cpp"
Import "gdal/gcore/gdalpamproxydb.cpp"
Import "gdal/gcore/gdalpamrasterband.cpp"
Import "gdal/gcore/gdalproxydataset.cpp"
Import "gdal/gcore/gdalproxypool.cpp"
Import "gdal/gcore/gdalrasterband.cpp"
Import "gdal/gcore/gdalrasterblock.cpp"
Import "gdal/gcore/overview.cpp"



Import "gdal/alg/*.h"

Import "gdal/alg/gdal_crs.c"
Import "gdal/alg/thinplatespline.cpp"
'Import "gdal/alg/gdal_nrgcrs.c"
Import "gdal/alg/contour.cpp"
Import "gdal/alg/gdal_rpc.cpp"
Import "gdal/alg/gdal_tps.cpp"
Import "gdal/alg/gdalchecksum.cpp"
Import "gdal/alg/gdalcutline.cpp"
Import "gdal/alg/gdaldither.cpp"
Import "gdal/alg/gdalgeoloc.cpp"
Import "gdal/alg/gdalgrid.cpp"
Import "gdal/alg/gdalmediancut.cpp"
Import "gdal/alg/gdalproximity.cpp"
Import "gdal/alg/gdalrasterize.cpp"
Import "gdal/alg/gdalrasterpolygonenumerator.cpp"
Import "gdal/alg/gdalsievefilter.cpp"
Import "gdal/alg/gdalsimplewarp.cpp"
Import "gdal/alg/gdaltransformer.cpp"
Import "gdal/alg/gdalwarper.cpp"
Import "gdal/alg/gdalwarpkernel.cpp"
Import "gdal/alg/gdalwarpoperation.cpp"
Import "gdal/alg/llrasterize.cpp"
Import "gdal/alg/polygonize.cpp"
Import "gdal/alg/rasterfill.cpp"


Import "gdal/frmts/gdalallregister.cpp"

' GEO TIFF
Import "gdal/frmts/gtiff/*.h"
Import "gdal/frmts/gtiff/libgeotiff/*.h"
Import "gdal/frmts/gtiff/libtiff/*.h"

Import "gdal/frmts/gtiff/geotiff.cpp"
Import "gdal/frmts/gtiff/gt_overview.cpp"
Import "gdal/frmts/gtiff/gt_wkt_srs.cpp"
Import "gdal/frmts/gtiff/tif_float.c"
Import "gdal/frmts/gtiff/tifvsi.cpp"

Import "gdal/frmts/gtiff/libgeotiff/xtiff.c"
Import "gdal/frmts/gtiff/libgeotiff/geo_free.c"
Import "gdal/frmts/gtiff/libgeotiff/geo_get.c"
Import "gdal/frmts/gtiff/libgeotiff/geo_names.c"
Import "gdal/frmts/gtiff/libgeotiff/geo_new.c"
Import "gdal/frmts/gtiff/libgeotiff/geo_print.c"
Import "gdal/frmts/gtiff/libgeotiff/geo_set.c"
Import "gdal/frmts/gtiff/libgeotiff/geo_tiffp.c"
Import "gdal/frmts/gtiff/libgeotiff/geo_write.c"
Import "gdal/frmts/gtiff/libgeotiff/geo_normalize.c"
Import "gdal/frmts/gtiff/libgeotiff/geotiff_proj4.c"
Import "gdal/frmts/gtiff/libgeotiff/geo_extra.c"
Import "gdal/frmts/gtiff/libgeotiff/geo_trans.c"

Import "gdal/frmts/gtiff/libtiff/tif_aux.c"
Import "gdal/frmts/gtiff/libtiff/tif_close.c"
Import "gdal/frmts/gtiff/libtiff/tif_codec.c"
Import "gdal/frmts/gtiff/libtiff/tif_color.c"
Import "gdal/frmts/gtiff/libtiff/tif_compress.c"
Import "gdal/frmts/gtiff/libtiff/tif_dir.c"
Import "gdal/frmts/gtiff/libtiff/tif_dirinfo.c"
Import "gdal/frmts/gtiff/libtiff/tif_dirread.c"
Import "gdal/frmts/gtiff/libtiff/tif_dirwrite.c"
Import "gdal/frmts/gtiff/libtiff/tif_dumpmode.c"
Import "gdal/frmts/gtiff/libtiff/tif_error.c"
Import "gdal/frmts/gtiff/libtiff/tif_extension.c"
Import "gdal/frmts/gtiff/libtiff/tif_fax3.c"
Import "gdal/frmts/gtiff/libtiff/tif_fax3sm.c"
Import "gdal/frmts/gtiff/libtiff/tif_getimage.c"
Import "gdal/frmts/gtiff/libtiff/tif_jpeg.c"
Import "gdal/frmts/gtiff/libtiff/tif_flush.c"
Import "gdal/frmts/gtiff/libtiff/tif_luv.c"
Import "gdal/frmts/gtiff/libtiff/tif_lzw.c"
Import "gdal/frmts/gtiff/libtiff/tif_next.c"
Import "gdal/frmts/gtiff/libtiff/tif_ojpeg.c"
Import "gdal/frmts/gtiff/libtiff/tif_open.c"
Import "gdal/frmts/gtiff/libtiff/tif_packbits.c"
Import "gdal/frmts/gtiff/libtiff/tif_pixarlog.c"
Import "gdal/frmts/gtiff/libtiff/tif_predict.c"
Import "gdal/frmts/gtiff/libtiff/tif_print.c"
Import "gdal/frmts/gtiff/libtiff/tif_read.c"
Import "gdal/frmts/gtiff/libtiff/tif_swab.c"
Import "gdal/frmts/gtiff/libtiff/tif_strip.c"
Import "gdal/frmts/gtiff/libtiff/tif_thunder.c"
Import "gdal/frmts/gtiff/libtiff/tif_tile.c"
Import "gdal/frmts/gtiff/libtiff/tif_vsi.c"
Import "gdal/frmts/gtiff/libtiff/tif_version.c"
Import "gdal/frmts/gtiff/libtiff/tif_warning.c"
Import "gdal/frmts/gtiff/libtiff/tif_write.c"
Import "gdal/frmts/gtiff/libtiff/tif_zip.c"


' iso8211
Import "gdal/frmts/iso8211/*.h"
Import "gdal/frmts/iso8211/ddfmodule.cpp"
Import "gdal/frmts/iso8211/ddfutils.cpp"
Import "gdal/frmts/iso8211/ddffielddefn.cpp"
Import "gdal/frmts/iso8211/ddfrecord.cpp"
Import "gdal/frmts/iso8211/ddffield.cpp"
Import "gdal/frmts/iso8211/ddfsubfielddefn.cpp"

' sdts
Import "gdal/frmts/sdts/*.h"
Import "gdal/frmts/sdts/sdtsiref.cpp"
Import "gdal/frmts/sdts/sdtscatd.cpp"
Import "gdal/frmts/sdts/sdtslinereader.cpp"
Import "gdal/frmts/sdts/sdtslib.cpp"
Import "gdal/frmts/sdts/sdtspointreader.cpp"
Import "gdal/frmts/sdts/sdtsattrreader.cpp"
Import "gdal/frmts/sdts/sdtstransfer.cpp"
Import "gdal/frmts/sdts/sdtspolygonreader.cpp"
Import "gdal/frmts/sdts/sdtsxref.cpp"
Import "gdal/frmts/sdts/sdtsrasterreader.cpp"
Import "gdal/frmts/sdts/sdtsindexedreader.cpp"
Import "gdal/frmts/sdts/sdtsdataset.cpp"

' mem
Import "gdal/frmts/mem/*.h"
Import "gdal/frmts/mem/memdataset.cpp"

' raw
Import "gdal/frmts/raw/*.h"
Import "gdal/frmts/raw/atlsci_spheroid.cpp"
Import "gdal/frmts/raw/rawdataset.cpp"
Import "gdal/frmts/raw/btdataset.cpp"
Import "gdal/frmts/raw/cpgdataset.cpp"
Import "gdal/frmts/raw/dipxdataset.cpp"
Import "gdal/frmts/raw/doq1dataset.cpp"
Import "gdal/frmts/raw/doq2dataset.cpp"
Import "gdal/frmts/raw/ehdrdataset.cpp"
Import "gdal/frmts/raw/eirdataset.cpp"
Import "gdal/frmts/raw/envidataset.cpp"
Import "gdal/frmts/raw/fastdataset.cpp"
Import "gdal/frmts/raw/fujibasdataset.cpp"
Import "gdal/frmts/raw/genbindataset.cpp"
Import "gdal/frmts/raw/gscdataset.cpp"
Import "gdal/frmts/raw/hkvdataset.cpp"
Import "gdal/frmts/raw/idadataset.cpp"
Import "gdal/frmts/raw/landataset.cpp"
Import "gdal/frmts/raw/lcpdataset.cpp"
Import "gdal/frmts/raw/mffdataset.cpp"
Import "gdal/frmts/raw/ndfdataset.cpp"
Import "gdal/frmts/raw/pauxdataset.cpp"
Import "gdal/frmts/raw/pnmdataset.cpp"

' vrt
Import "gdal/frmts/vrt/*.h"
Import "gdal/frmts/vrt/vrtdataset.cpp"
Import "gdal/frmts/vrt/vrtwarped.cpp"
Import "gdal/frmts/vrt/vrtderivedrasterband.cpp"
Import "gdal/frmts/vrt/vrtdriver.cpp"
Import "gdal/frmts/vrt/vrtfilters.cpp"
Import "gdal/frmts/vrt/vrtrasterband.cpp"
Import "gdal/frmts/vrt/vrtrawrasterband.cpp"
Import "gdal/frmts/vrt/vrtsourcedrasterband.cpp"
Import "gdal/frmts/vrt/vrtsources.cpp"

' nitf
Import "gdal/frmts/nitf/*.h"
Import "gdal/frmts/nitf/rpftocfile.cpp"
Import "gdal/frmts/nitf/nitfaridpcm.cpp"
Import "gdal/frmts/nitf/nitfbilevel.cpp"
Import "gdal/frmts/nitf/nitfdataset.cpp"
Import "gdal/frmts/nitf/nitffile.c"
Import "gdal/frmts/nitf/nitfimage.c"
Import "gdal/frmts/nitf/rpftocdataset.cpp"
Import "gdal/frmts/nitf/mgrs.c"

' png
Import "gdal/frmts/png/*.h"
Import "gdal/frmts/png/pngdataset.cpp"

' terragen
Import "gdal/frmts/terragen/*.h"
Import "gdal/frmts/terragen/terragendataset.cpp"

' bmp
Import "gdal/frmts/bmp/*.h"
Import "gdal/frmts/bmp/bmpdataset.cpp"

' airsar
Import "gdal/frmts/airsar/*.h"
Import "gdal/frmts/airsar/airsardataset.cpp"

' l1b
Import "gdal/frmts/l1b/*.h"
Import "gdal/frmts/l1b/l1bdataset.cpp"

' pds
Import "gdal/frmts/pds/*.h"
Import "gdal/frmts/pds/isis2dataset.cpp"
Import "gdal/frmts/pds/isis3dataset.cpp"
Import "gdal/frmts/pds/nasakeywordhandler.cpp"
Import "gdal/frmts/pds/pdsdataset.cpp"

' gxf
Import "gdal/frmts/gxf/*.h"
Import "gdal/frmts/gxf/gxfopen.c"
Import "gdal/frmts/gxf/gxf_proj4.c"
Import "gdal/frmts/gxf/gxf_ogcwkt.c"
Import "gdal/frmts/gxf/gxfdataset.cpp"

' tsx
Import "gdal/frmts/tsx/*.h"
Import "gdal/frmts/tsx/tsxdataset.cpp"

' usgsdem
Import "gdal/frmts/usgsdem/*.h"
Import "gdal/frmts/usgsdem/usgsdem_create.cpp"
Import "gdal/frmts/usgsdem/usgsdemdataset.cpp"

' pcraster
Import "gdal/frmts/pcraster/*.h"
Import "gdal/frmts/pcraster/libcsf/*.h"
Import "gdal/frmts/pcraster/pcrasterutil.cpp"
Import "gdal/frmts/pcraster/pcrasterrasterband.cpp"
Import "gdal/frmts/pcraster/pcrasterdataset.cpp"
Import "gdal/frmts/pcraster/pcrastermisc.cpp"
Import "gdal/frmts/pcraster/libcsf/_getcell.c"
Import "gdal/frmts/pcraster/libcsf/wattrblk.c"
Import "gdal/frmts/pcraster/libcsf/_getrow.c"
Import "gdal/frmts/pcraster/libcsf/_gsomece.c"
Import "gdal/frmts/pcraster/libcsf/_putcell.c"
Import "gdal/frmts/pcraster/libcsf/_rputrow.c"
Import "gdal/frmts/pcraster/libcsf/angle.c"
Import "gdal/frmts/pcraster/libcsf/attravai.c"
Import "gdal/frmts/pcraster/libcsf/attrsize.c"
Import "gdal/frmts/pcraster/libcsf/cellsize.c"
Import "gdal/frmts/pcraster/libcsf/create2.c"
Import "gdal/frmts/pcraster/libcsf/csfglob.c"
Import "gdal/frmts/pcraster/libcsf/csfsup.c"
Import "gdal/frmts/pcraster/libcsf/delattr.c"
Import "gdal/frmts/pcraster/libcsf/dumconv.c"
Import "gdal/frmts/pcraster/libcsf/endian.c"
Import "gdal/frmts/pcraster/libcsf/filename.c"
Import "gdal/frmts/pcraster/libcsf/gattrblk.c"
Import "gdal/frmts/pcraster/libcsf/gattridx.c"
Import "gdal/frmts/pcraster/libcsf/gcellrep.c"
Import "gdal/frmts/pcraster/libcsf/gdattype.c"
Import "gdal/frmts/pcraster/libcsf/getattr.c"
Import "gdal/frmts/pcraster/libcsf/getx0.c"
Import "gdal/frmts/pcraster/libcsf/gety0.c"
Import "gdal/frmts/pcraster/libcsf/ggisfid.c"
Import "gdal/frmts/pcraster/libcsf/gmaxval.c"
Import "gdal/frmts/pcraster/libcsf/gminval.c"
Import "gdal/frmts/pcraster/libcsf/gnrcols.c"
Import "gdal/frmts/pcraster/libcsf/gnrrows.c"
Import "gdal/frmts/pcraster/libcsf/gproj.c"
Import "gdal/frmts/pcraster/libcsf/gputproj.c"
Import "gdal/frmts/pcraster/libcsf/gvalscal.c"
Import "gdal/frmts/pcraster/libcsf/gvartype.c"
Import "gdal/frmts/pcraster/libcsf/gversion.c"
Import "gdal/frmts/pcraster/libcsf/ismv.c"
Import "gdal/frmts/pcraster/libcsf/kernlcsf.c"
Import "gdal/frmts/pcraster/libcsf/legend.c"
Import "gdal/frmts/pcraster/libcsf/mclose.c"
Import "gdal/frmts/pcraster/libcsf/mopen.c"
Import "gdal/frmts/pcraster/libcsf/moreattr.c"
Import "gdal/frmts/pcraster/libcsf/mperror.c"
Import "gdal/frmts/pcraster/libcsf/pgisfid.c"
Import "gdal/frmts/pcraster/libcsf/pmaxval.c"
Import "gdal/frmts/pcraster/libcsf/pminval.c"
Import "gdal/frmts/pcraster/libcsf/putallmv.c"
Import "gdal/frmts/pcraster/libcsf/putattr.c"
Import "gdal/frmts/pcraster/libcsf/putsomec.c"
Import "gdal/frmts/pcraster/libcsf/putx0.c"
Import "gdal/frmts/pcraster/libcsf/puty0.c"
Import "gdal/frmts/pcraster/libcsf/pvalscal.c"
Import "gdal/frmts/pcraster/libcsf/rattrblk.c"
Import "gdal/frmts/pcraster/libcsf/rcomp.c"
Import "gdal/frmts/pcraster/libcsf/rcoords.c"
Import "gdal/frmts/pcraster/libcsf/rdup2.c"
Import "gdal/frmts/pcraster/libcsf/reseterr.c"
Import "gdal/frmts/pcraster/libcsf/rextend.c"
Import "gdal/frmts/pcraster/libcsf/rmalloc.c"
Import "gdal/frmts/pcraster/libcsf/rrowcol.c"
Import "gdal/frmts/pcraster/libcsf/ruseas.c"
Import "gdal/frmts/pcraster/libcsf/setangle.c"
Import "gdal/frmts/pcraster/libcsf/setmv.c"
Import "gdal/frmts/pcraster/libcsf/setvtmv.c"
Import "gdal/frmts/pcraster/libcsf/strconst.c"
Import "gdal/frmts/pcraster/libcsf/strpad.c"
Import "gdal/frmts/pcraster/libcsf/swapio.c"
Import "gdal/frmts/pcraster/libcsf/trackmm.c"
Import "gdal/frmts/pcraster/libcsf/vs2.c"
Import "gdal/frmts/pcraster/libcsf/vsdef.c"
Import "gdal/frmts/pcraster/libcsf/vsis.c"
Import "gdal/frmts/pcraster/libcsf/vsvers.c"

' gif
Import "gdal/frmts/gif/*.h"
Import "gdal/frmts/gif/libungif/*.h"
Import "gdal/frmts/gif/libungif/dgif_lib.c"
Import "gdal/frmts/gif/libungif/gif_err.c"
Import "gdal/frmts/gif/libungif/egif_lib.c"
Import "gdal/frmts/gif/libungif/gifalloc.c"
Import "gdal/frmts/gif/gifdataset.cpp"

' gff
Import "gdal/frmts/gff/*.h"
Import "gdal/frmts/gff/gff_dataset.cpp"

' cosar
Import "gdal/frmts/cosar/*.h"
Import "gdal/frmts/cosar/cosar_dataset.cpp"

' ingr
Import "gdal/frmts/ingr/*.h"
Import "gdal/frmts/ingr/IngrTypes.cpp"
Import "gdal/frmts/ingr/IntergraphBand.cpp"
Import "gdal/frmts/ingr/IntergraphDataset.cpp"
Import "gdal/frmts/ingr/JpegHelper.cpp"

' dted
Import "gdal/frmts/dted/*.h"
Import "gdal/frmts/dted/dted_api.c"
Import "gdal/frmts/dted/dted_create.c"
Import "gdal/frmts/dted/dted_ptstream.c"
Import "gdal/frmts/dted/dteddataset.cpp"

' msgn
Import "gdal/frmts/msgn/*.h"
Import "gdal/frmts/msgn/msg_basic_types.cpp"
Import "gdal/frmts/msgn/msg_reader_core.cpp"
Import "gdal/frmts/msgn/msgndataset.cpp"

' aaigrid
Import "gdal/frmts/aaigrid/*.h"
Import "gdal/frmts/aaigrid/aaigriddataset.cpp"

' gsg
Import "gdal/frmts/gsg/*.h"
Import "gdal/frmts/gsg/gs7bgdataset.cpp"
Import "gdal/frmts/gsg/gsbgdataset.cpp"
Import "gdal/frmts/gsg/gsagdataset.cpp"

' blx
Import "gdal/frmts/blx/*.h"
Import "gdal/frmts/blx/blxdataset.cpp"
Import "gdal/frmts/blx/blx.c"

' wms
Import "gdal/frmts/wms/*.h"
Import "gdal/frmts/wms/wmsdriver.cpp"
Import "gdal/frmts/wms/stuff.cpp"
Import "gdal/frmts/wms/rasterband.cpp"
Import "gdal/frmts/wms/minidriver.cpp"
Import "gdal/frmts/wms/minidriver_worldwind.cpp"
Import "gdal/frmts/wms/minidriver_wms.cpp"
Import "gdal/frmts/wms/minidriver_tileservice.cpp"
Import "gdal/frmts/wms/gdalhttp.cpp"
Import "gdal/frmts/wms/cache.cpp"
Import "gdal/frmts/wms/dataset.cpp"
Import "gdal/frmts/wms/md5.cpp"

' wcs
Import "gdal/frmts/wcs/*.h"
Import "gdal/frmts/wcs/httpdriver.cpp"
Import "gdal/frmts/wcs/wcsdataset.cpp"

' rs2
Import "gdal/frmts/rs2/*.h"
Import "gdal/frmts/rs2/rs2dataset.cpp"

' bsb
Import "gdal/frmts/bsb/*.h"
Import "gdal/frmts/bsb/bsb_read.c"
Import "gdal/frmts/bsb/bsb2raw.c"
Import "gdal/frmts/bsb/bsbdataset.cpp"

' ceos
Import "gdal/frmts/ceos/*.h"
Import "gdal/frmts/ceos/ceosdataset.cpp"
Import "gdal/frmts/ceos/ceosopen.c"

' elas
Import "gdal/frmts/elas/*.h"
Import "gdal/frmts/elas/elasdataset.cpp"

' coasp
Import "gdal/frmts/coasp/*.h"
Import "gdal/frmts/coasp/coasp_dataset.cpp"

' rmf
Import "gdal/frmts/rmf/*.h"
Import "gdal/frmts/rmf/rmflzw.cpp"
Import "gdal/frmts/rmf/rmfdataset.cpp"

' adrg
Import "gdal/frmts/adrg/*.h"
Import "gdal/frmts/adrg/adrgdataset.cpp"

' ers
Import "gdal/frmts/ers/*.h"
Import "gdal/frmts/ers/ersdataset.cpp"
Import "gdal/frmts/ers/ershdrnode.cpp"

' fit
Import "gdal/frmts/fit/*.h"
Import "gdal/frmts/fit/fit.cpp"
Import "gdal/frmts/fit/fitdataset.cpp"

' envisat
Import "gdal/frmts/envisat/*.h"
Import "gdal/frmts/envisat/envisatdataset.cpp"
Import "gdal/frmts/envisat/EnvisatFile.c"

' ilwis
Import "gdal/frmts/ilwis/*.h"
Import "gdal/frmts/ilwis/ilwisdataset.cpp"
Import "gdal/frmts/ilwis/ilwiscoordinatesystem.cpp"

' jaxapalsar
Import "gdal/frmts/jaxapalsar/*.h"
Import "gdal/frmts/jaxapalsar/jaxapalsardataset.cpp"

' jdem
Import "gdal/frmts/jdem/*.h"
Import "gdal/frmts/jdem/jdemdataset.cpp"

' leveller
Import "gdal/frmts/leveller/*.h"
Import "gdal/frmts/leveller/levellerdataset.cpp"

' ceos2
Import "gdal/frmts/ceos2/*.h"
Import "gdal/frmts/ceos2/sar_ceosdataset.cpp"
Import "gdal/frmts/ceos2/link.c"
Import "gdal/frmts/ceos2/ceossar.c"
Import "gdal/frmts/ceos2/ceosrecipe.c"
Import "gdal/frmts/ceos2/ceos.c"

' pcidsk
Import "gdal/frmts/pcidsk/*.h"
Import "gdal/frmts/pcidsk/pcidsktiledrasterband.cpp"
Import "gdal/frmts/pcidsk/pcidskdataset.cpp"

' sgi
Import "gdal/frmts/sgi/*.h"
Import "gdal/frmts/sgi/sgidataset.cpp"

' dimap
Import "gdal/frmts/dimap/*.h"
Import "gdal/frmts/dimap/dimapdataset.cpp"

' idrisi
Import "gdal/frmts/idrisi/*.h"
Import "gdal/frmts/idrisi/IdrisiDataset.cpp"

' xpm
Import "gdal/frmts/xpm/*.h"
Import "gdal/frmts/xpm/xpmdataset.cpp"

' jpeg
Import "gdal/frmts/jpeg/*.h"
Import "gdal/frmts/jpeg/jpgdataset.cpp"
Import "gdal/frmts/jpeg/vsidataio.cpp"

' OGR
Import "gdal/ogr/*.h"
Import "gdal/ogr/ogrsf_frmts/*.h"

Import "gdal/ogr/ogrgeometryfactory.cpp"
Import "gdal/ogr/ogrpoint.cpp"
Import "gdal/ogr/ogrcurve.cpp"
Import "gdal/ogr/ogrlinestring.cpp"
Import "gdal/ogr/ogrlinearring.cpp"
Import "gdal/ogr/ogrpolygon.cpp"
Import "gdal/ogr/ogrutils.cpp"
Import "gdal/ogr/ogrgeometry.cpp"
Import "gdal/ogr/ogrgeometrycollection.cpp"
Import "gdal/ogr/ogrmultipolygon.cpp"
Import "gdal/ogr/ogrsurface.cpp"
Import "gdal/ogr/ogrmultipoint.cpp"
Import "gdal/ogr/ogrmultilinestring.cpp"
Import "gdal/ogr/ogr_api.cpp"
Import "gdal/ogr/ogrfeature.cpp"
Import "gdal/ogr/ogrfeaturedefn.cpp"
Import "gdal/ogr/ogrfeaturequery.cpp"
Import "gdal/ogr/ogrfeaturestyle.cpp"
Import "gdal/ogr/ogrfielddefn.cpp"
Import "gdal/ogr/ogrspatialreference.cpp"
Import "gdal/ogr/ogr_srsnode.cpp"
Import "gdal/ogr/ogr_srs_proj4.cpp"
Import "gdal/ogr/ogr_fromepsg.cpp"
Import "gdal/ogr/ogrct.cpp"
Import "gdal/ogr/ogr_opt.cpp"
Import "gdal/ogr/ogr_srs_esri.cpp"
Import "gdal/ogr/ogr_srs_pci.cpp"
Import "gdal/ogr/ogr_srs_usgs.cpp"
Import "gdal/ogr/ogr_srs_dict.cpp"
Import "gdal/ogr/ogr_srs_panorama.cpp"
Import "gdal/ogr/ogr_srs_erm.cpp"
Import "gdal/ogr/swq.c"
Import "gdal/ogr/ogr_srs_validate.cpp"
Import "gdal/ogr/ogr_srs_xml.cpp"
Import "gdal/ogr/ograssemblepolygon.cpp"
Import "gdal/ogr/ogr2gmlgeometry.cpp"
Import "gdal/ogr/gml2ogrgeometry.cpp"


' OGR - generic
Import "gdal/ogr/ogrsf_frmts/generic/*.h"
Import "gdal/ogr/ogrsf_frmts/generic/ogr_attrind.cpp"
Import "gdal/ogr/ogrsf_frmts/generic/ogrsfdriverregistrar.cpp"
Import "gdal/ogr/ogrsf_frmts/generic/ogr_gensql.cpp"
Import "gdal/ogr/ogrsf_frmts/generic/ogr_miattrind.cpp"
Import "gdal/ogr/ogrsf_frmts/generic/ogrdatasource.cpp"
Import "gdal/ogr/ogrsf_frmts/generic/ogrlayer.cpp"
Import "gdal/ogr/ogrsf_frmts/generic/ogrregisterall.cpp"
Import "gdal/ogr/ogrsf_frmts/generic/ogrsfdriver.cpp"

' OGR - shape
Import "gdal/ogr/ogrsf_frmts/shape/*.h"
Import "gdal/ogr/ogrsf_frmts/shape/dbfopen.c"
Import "gdal/ogr/ogrsf_frmts/shape/shape2ogr.cpp"
Import "gdal/ogr/ogrsf_frmts/shape/shp_vsi.c"
Import "gdal/ogr/ogrsf_frmts/shape/shpopen.c"
Import "gdal/ogr/ogrsf_frmts/shape/shptree.c"
Import "gdal/ogr/ogrsf_frmts/shape/ogrshapedatasource.cpp"
Import "gdal/ogr/ogrsf_frmts/shape/ogrshapedriver.cpp"
Import "gdal/ogr/ogrsf_frmts/shape/ogrshapelayer.cpp"

' OGR - avc
Import "gdal/ogr/ogrsf_frmts/avc/*.h"
Import "gdal/ogr/ogrsf_frmts/avc/ogravcbindriver.cpp"
Import "gdal/ogr/ogrsf_frmts/avc/ogravcbindatasource.cpp"
Import "gdal/ogr/ogrsf_frmts/avc/ogravcbinlayer.cpp"
Import "gdal/ogr/ogrsf_frmts/avc/ogravclayer.cpp"
Import "gdal/ogr/ogrsf_frmts/avc/ogravcdatasource.cpp"
Import "gdal/ogr/ogrsf_frmts/avc/ogravce00layer.cpp"
Import "gdal/ogr/ogrsf_frmts/avc/ogravce00datasource.cpp"
Import "gdal/ogr/ogrsf_frmts/avc/ogravce00driver.cpp"
Import "gdal/ogr/ogrsf_frmts/avc/avc_bin.c"
Import "gdal/ogr/ogrsf_frmts/avc/avc_binwr.c"
Import "gdal/ogr/ogrsf_frmts/avc/avc_e00gen.c"
Import "gdal/ogr/ogrsf_frmts/avc/avc_e00parse.c"
Import "gdal/ogr/ogrsf_frmts/avc/avc_e00write.c"
Import "gdal/ogr/ogrsf_frmts/avc/avc_e00read.c"
Import "gdal/ogr/ogrsf_frmts/avc/avc_mbyte.c"
Import "gdal/ogr/ogrsf_frmts/avc/avc_misc.c"
Import "gdal/ogr/ogrsf_frmts/avc/avc_rawbin.c"


' OGR - bna
Import "gdal/ogr/ogrsf_frmts/bna/*.h"
Import "gdal/ogr/ogrsf_frmts/bna/ogrbnadatasource.cpp"
Import "gdal/ogr/ogrsf_frmts/bna/ogrbnaparser.cpp"
Import "gdal/ogr/ogrsf_frmts/bna/ogrbnadriver.cpp"
Import "gdal/ogr/ogrsf_frmts/bna/ogrbnalayer.cpp"

' OGR - dgn
Import "gdal/ogr/ogrsf_frmts/dgn/*.h"
Import "gdal/ogr/ogrsf_frmts/dgn/dgnopen.cpp"
Import "gdal/ogr/ogrsf_frmts/dgn/dgnread.cpp"
Import "gdal/ogr/ogrsf_frmts/dgn/dgnfloat.cpp"
Import "gdal/ogr/ogrsf_frmts/dgn/dgnhelp.cpp"
Import "gdal/ogr/ogrsf_frmts/dgn/dgnwrite.cpp"
Import "gdal/ogr/ogrsf_frmts/dgn/dgnstroke.cpp"
Import "gdal/ogr/ogrsf_frmts/dgn/ogrdgndriver.cpp"
Import "gdal/ogr/ogrsf_frmts/dgn/ogrdgndatasource.cpp"
Import "gdal/ogr/ogrsf_frmts/dgn/ogrdgnlayer.cpp"


' OGR - mem
Import "gdal/ogr/ogrsf_frmts/mem/*.h"
Import "gdal/ogr/ogrsf_frmts/mem/ogrmemlayer.cpp"
Import "gdal/ogr/ogrsf_frmts/mem/ogrmemdatasource.cpp"
Import "gdal/ogr/ogrsf_frmts/mem/ogrmemdriver.cpp"

' OGR - csv
Import "gdal/ogr/ogrsf_frmts/csv/*.h"
Import "gdal/ogr/ogrsf_frmts/csv/ogrcsvdatasource.cpp"
Import "gdal/ogr/ogrsf_frmts/csv/ogrcsvlayer.cpp"
Import "gdal/ogr/ogrsf_frmts/csv/ogrcsvdriver.cpp"

' OGR - geojson
Import "gdal/ogr/ogrsf_frmts/geojson/*.h"
Import "gdal/ogr/ogrsf_frmts/geojson/jsonc/*.h"

Import "gdal/ogr/ogrsf_frmts/geojson/ogrgeojsondatasource.cpp"
Import "gdal/ogr/ogrsf_frmts/geojson/ogrgeojsonwriter.cpp"
Import "gdal/ogr/ogrsf_frmts/geojson/ogrgeojsondriver.cpp"
Import "gdal/ogr/ogrsf_frmts/geojson/ogrgeojsonlayer.cpp"
Import "gdal/ogr/ogrsf_frmts/geojson/ogrgeojsonreader.cpp"
Import "gdal/ogr/ogrsf_frmts/geojson/ogrgeojsonutils.cpp"
Import "gdal/ogr/ogrsf_frmts/geojson/jsonc/arraylist.c"
Import "gdal/ogr/ogrsf_frmts/geojson/jsonc/debug.c"
Import "gdal/ogr/ogrsf_frmts/geojson/jsonc/json_object.c"
Import "gdal/ogr/ogrsf_frmts/geojson/jsonc/json_tokener.c"
Import "gdal/ogr/ogrsf_frmts/geojson/jsonc/json_util.c"
Import "gdal/ogr/ogrsf_frmts/geojson/jsonc/linkhash.c"
Import "gdal/ogr/ogrsf_frmts/geojson/jsonc/printbuf.c"

' OGR - gml
Import "gdal/ogr/ogrsf_frmts/gml/*.h"
Import "gdal/ogr/ogrsf_frmts/gml/gmlpropertydefn.cpp"
Import "gdal/ogr/ogrsf_frmts/gml/gmlfeatureclass.cpp"
Import "gdal/ogr/ogrsf_frmts/gml/gmlfeature.cpp"
Import "gdal/ogr/ogrsf_frmts/gml/gmlreader.cpp"
Import "gdal/ogr/ogrsf_frmts/gml/parsexsd.cpp"
Import "gdal/ogr/ogrsf_frmts/gml/ogrgmldriver.cpp"
Import "gdal/ogr/ogrsf_frmts/gml/ogrgmldatasource.cpp"
Import "gdal/ogr/ogrsf_frmts/gml/ogrgmllayer.cpp"


' OGR - gmt
Import "gdal/ogr/ogrsf_frmts/gmt/*.h"
Import "gdal/ogr/ogrsf_frmts/gmt/ogrgmtdatasource.cpp"
Import "gdal/ogr/ogrsf_frmts/gmt/ogrgmtlayer.cpp"
Import "gdal/ogr/ogrsf_frmts/gmt/ogrgmtdriver.cpp"

' OGR - kml
Import "gdal/ogr/ogrsf_frmts/kml/*.h"
Import "gdal/ogr/ogrsf_frmts/kml/kml.cpp"
Import "gdal/ogr/ogrsf_frmts/kml/ogrkmllayer.cpp"
Import "gdal/ogr/ogrsf_frmts/kml/kmlnode.cpp"
Import "gdal/ogr/ogrsf_frmts/kml/kmlvector.cpp"
Import "gdal/ogr/ogrsf_frmts/kml/ogr2kmlgeometry.cpp"
Import "gdal/ogr/ogrsf_frmts/kml/ogrkmldatasource.cpp"
Import "gdal/ogr/ogrsf_frmts/kml/ogrkmldriver.cpp"

' OGR - mitab
Import "gdal/ogr/ogrsf_frmts/mitab/*.h"
Import "gdal/ogr/ogrsf_frmts/mitab/mitab_bounds.cpp"
Import "gdal/ogr/ogrsf_frmts/mitab/mitab_utils.cpp"
Import "gdal/ogr/ogrsf_frmts/mitab/mitab_coordsys.cpp"
Import "gdal/ogr/ogrsf_frmts/mitab/mitab_datfile.cpp"
Import "gdal/ogr/ogrsf_frmts/mitab/mitab_feature_mif.cpp"
Import "gdal/ogr/ogrsf_frmts/mitab/mitab_feature.cpp"
Import "gdal/ogr/ogrsf_frmts/mitab/mitab_geometry.cpp"
Import "gdal/ogr/ogrsf_frmts/mitab/mitab_idfile.cpp"
Import "gdal/ogr/ogrsf_frmts/mitab/mitab_imapinfofile.cpp"
Import "gdal/ogr/ogrsf_frmts/mitab/mitab_indfile.cpp"
Import "gdal/ogr/ogrsf_frmts/mitab/mitab_mapcoordblock.cpp"
Import "gdal/ogr/ogrsf_frmts/mitab/mitab_mapfile.cpp"
Import "gdal/ogr/ogrsf_frmts/mitab/mitab_mapheaderblock.cpp"
Import "gdal/ogr/ogrsf_frmts/mitab/mitab_mapindexblock.cpp"
Import "gdal/ogr/ogrsf_frmts/mitab/mitab_mapobjectblock.cpp"
Import "gdal/ogr/ogrsf_frmts/mitab/mitab_maptoolblock.cpp"
Import "gdal/ogr/ogrsf_frmts/mitab/mitab_middatafile.cpp"
Import "gdal/ogr/ogrsf_frmts/mitab/mitab_miffile.cpp"
Import "gdal/ogr/ogrsf_frmts/mitab/mitab_ogr_datasource.cpp"
Import "gdal/ogr/ogrsf_frmts/mitab/mitab_ogr_driver.cpp"
Import "gdal/ogr/ogrsf_frmts/mitab/mitab_rawbinblock.cpp"
Import "gdal/ogr/ogrsf_frmts/mitab/mitab_spatialref.cpp"
Import "gdal/ogr/ogrsf_frmts/mitab/mitab_tabfile.cpp"
Import "gdal/ogr/ogrsf_frmts/mitab/mitab_tabseamless.cpp"
Import "gdal/ogr/ogrsf_frmts/mitab/mitab_tabview.cpp"
Import "gdal/ogr/ogrsf_frmts/mitab/mitab_tooldef.cpp"

' OGR - ntf
Import "gdal/ogr/ogrsf_frmts/ntf/*.h"
Import "gdal/ogr/ogrsf_frmts/ntf/ntf_codelist.cpp"
Import "gdal/ogr/ogrsf_frmts/ntf/ogrntflayer.cpp"
Import "gdal/ogr/ogrsf_frmts/ntf/ntf_estlayers.cpp"
Import "gdal/ogr/ogrsf_frmts/ntf/ntf_generic.cpp"
Import "gdal/ogr/ogrsf_frmts/ntf/ntf_raster.cpp"
Import "gdal/ogr/ogrsf_frmts/ntf/ntfdump.cpp"
Import "gdal/ogr/ogrsf_frmts/ntf/ntffilereader.cpp"
Import "gdal/ogr/ogrsf_frmts/ntf/ntfrecord.cpp"
Import "gdal/ogr/ogrsf_frmts/ntf/ntfstroke.cpp"
Import "gdal/ogr/ogrsf_frmts/ntf/ogrntfdatasource.cpp"
Import "gdal/ogr/ogrsf_frmts/ntf/ogrntfdriver.cpp"
Import "gdal/ogr/ogrsf_frmts/ntf/ogrntffeatureclasslayer.cpp"

' OGR - gpx
Import "gdal/ogr/ogrsf_frmts/gpx/*.h"
Import "gdal/ogr/ogrsf_frmts/gpx/ogrgpxdatasource.cpp"
Import "gdal/ogr/ogrsf_frmts/gpx/ogrgpxlayer.cpp"
Import "gdal/ogr/ogrsf_frmts/gpx/ogrgpxdriver.cpp"

' OGR - rec
Import "gdal/ogr/ogrsf_frmts/rec/*.h"
Import "gdal/ogr/ogrsf_frmts/rec/ll_recio.cpp"
Import "gdal/ogr/ogrsf_frmts/rec/ogrreclayer.cpp"
Import "gdal/ogr/ogrsf_frmts/rec/ogrrecdatasource.cpp"
Import "gdal/ogr/ogrsf_frmts/rec/ogrrecdriver.cpp"

' OGR - s57
Import "gdal/ogr/ogrsf_frmts/s57/*.h"
Import "gdal/ogr/ogrsf_frmts/s57/ogrs57driver.cpp"
Import "gdal/ogr/ogrsf_frmts/s57/ogrs57datasource.cpp"
Import "gdal/ogr/ogrsf_frmts/s57/ogrs57layer.cpp"
Import "gdal/ogr/ogrsf_frmts/s57/s57reader.cpp"
Import "gdal/ogr/ogrsf_frmts/s57/s57writer.cpp"
Import "gdal/ogr/ogrsf_frmts/s57/ddfrecordindex.cpp"
Import "gdal/ogr/ogrsf_frmts/s57/s57classregistrar.cpp"
Import "gdal/ogr/ogrsf_frmts/s57/s57filecollector.cpp"
Import "gdal/ogr/ogrsf_frmts/s57/s57featuredefns.cpp"

' OGR - sdts
Import "gdal/ogr/ogrsf_frmts/sdts/*.h"
Import "gdal/ogr/ogrsf_frmts/sdts/ogrsdtsdatasource.cpp"
Import "gdal/ogr/ogrsf_frmts/sdts/ogrsdtslayer.cpp"
Import "gdal/ogr/ogrsf_frmts/sdts/ogrsdtsdriver.cpp"

' OGR - tiger
Import "gdal/ogr/ogrsf_frmts/tiger/*.h"
Import "gdal/ogr/ogrsf_frmts/tiger/ogrtigerdatasource.cpp"
Import "gdal/ogr/ogrsf_frmts/tiger/tigerzipplus4.cpp"
Import "gdal/ogr/ogrsf_frmts/tiger/ogrtigerdriver.cpp"
Import "gdal/ogr/ogrsf_frmts/tiger/ogrtigerlayer.cpp"
Import "gdal/ogr/ogrsf_frmts/tiger/tigeraltname.cpp"
Import "gdal/ogr/ogrsf_frmts/tiger/tigerarealandmarks.cpp"
Import "gdal/ogr/ogrsf_frmts/tiger/tigercompletechain.cpp"
Import "gdal/ogr/ogrsf_frmts/tiger/tigerentitynames.cpp"
Import "gdal/ogr/ogrsf_frmts/tiger/tigerfeatureids.cpp"
Import "gdal/ogr/ogrsf_frmts/tiger/tigerfilebase.cpp"
Import "gdal/ogr/ogrsf_frmts/tiger/tigeridhistory.cpp"
Import "gdal/ogr/ogrsf_frmts/tiger/tigerkeyfeatures.cpp"
Import "gdal/ogr/ogrsf_frmts/tiger/tigerlandmarks.cpp"
Import "gdal/ogr/ogrsf_frmts/tiger/tigeroverunder.cpp"
Import "gdal/ogr/ogrsf_frmts/tiger/tigerpip.cpp"
Import "gdal/ogr/ogrsf_frmts/tiger/tigerpoint.cpp"
Import "gdal/ogr/ogrsf_frmts/tiger/tigerpolychainlink.cpp"
Import "gdal/ogr/ogrsf_frmts/tiger/tigerpolygon.cpp"
Import "gdal/ogr/ogrsf_frmts/tiger/tigerpolygoncorrections.cpp"
Import "gdal/ogr/ogrsf_frmts/tiger/tigerpolygoneconomic.cpp"
Import "gdal/ogr/ogrsf_frmts/tiger/tigerspatialmetadata.cpp"
Import "gdal/ogr/ogrsf_frmts/tiger/tigertlidrange.cpp"
Import "gdal/ogr/ogrsf_frmts/tiger/tigerzerocellid.cpp"
Import "gdal/ogr/ogrsf_frmts/tiger/tigerzipcodes.cpp"

' OGR - vrt
Import "gdal/ogr/ogrsf_frmts/vrt/*.h"
Import "gdal/ogr/ogrsf_frmts/vrt/ogrvrtdatasource.cpp"
Import "gdal/ogr/ogrsf_frmts/vrt/ogrvrtlayer.cpp"
Import "gdal/ogr/ogrsf_frmts/vrt/ogrvrtdriver.cpp"

' OGR - geoconcept
Import "gdal/ogr/ogrsf_frmts/geoconcept/*.h"
Import "gdal/ogr/ogrsf_frmts/geoconcept/geoconcept_syscoord.c"
Import "gdal/ogr/ogrsf_frmts/geoconcept/ogrgeoconceptlayer.cpp"
Import "gdal/ogr/ogrsf_frmts/geoconcept/geoconcept.c"
Import "gdal/ogr/ogrsf_frmts/geoconcept/ogrgeoconceptdatasource.cpp"
Import "gdal/ogr/ogrsf_frmts/geoconcept/ogrgeoconceptdriver.cpp"

' OGR - xplane
Import "gdal/ogr/ogrsf_frmts/xplane/*.h"
Import "gdal/ogr/ogrsf_frmts/xplane/ogrxplanedriver.cpp"
Import "gdal/ogr/ogrsf_frmts/xplane/ogrxplanedatasource.cpp"
Import "gdal/ogr/ogrsf_frmts/xplane/ogrxplanelayer.cpp"
Import "gdal/ogr/ogrsf_frmts/xplane/ogr_xplane_geo_utils.cpp"
Import "gdal/ogr/ogrsf_frmts/xplane/ogr_xplane_reader.cpp"
Import "gdal/ogr/ogrsf_frmts/xplane/ogr_xplane_apt_reader.cpp"
Import "gdal/ogr/ogrsf_frmts/xplane/ogr_xplane_nav_reader.cpp"
Import "gdal/ogr/ogrsf_frmts/xplane/ogr_xplane_fix_reader.cpp"
Import "gdal/ogr/ogrsf_frmts/xplane/ogr_xplane_awy_reader.cpp"

' HFA
Import "gdal/frmts/hfa/*.h"
Import "gdal/frmts/hfa/hfaopen.cpp"
Import "gdal/frmts/hfa/hfaentry.cpp"
Import "gdal/frmts/hfa/hfadictionary.cpp"
Import "gdal/frmts/hfa/hfafield.cpp"
Import "gdal/frmts/hfa/hfatype.cpp"
Import "gdal/frmts/hfa/hfaband.cpp"
Import "gdal/frmts/hfa/hfacompress.cpp"
Import "gdal/frmts/hfa/hfadataset.cpp"
Import "gdal/frmts/hfa/hfa_overviews.cpp"


' aigrid
Import "gdal/frmts/aigrid/*.h"
Import "gdal/frmts/aigrid/gridlib.c"
Import "gdal/frmts/aigrid/aigopen.c"
Import "gdal/frmts/aigrid/aigccitt.c"
Import "gdal/frmts/aigrid/aigdataset.cpp"

' SRTM HGT
Import "gdal/frmts/srtmhgt/srtmhgtdataset.cpp"


' PROJ.4
Import "gdal/proj/src/PJ_aeqd.c"
Import "gdal/proj/src/PJ_gnom.c"
Import "gdal/proj/src/PJ_laea.c"
Import "gdal/proj/src/PJ_mod_ster.c"
Import "gdal/proj/src/PJ_nsper.c"
Import "gdal/proj/src/PJ_nzmg.c"
Import "gdal/proj/src/PJ_ortho.c"
Import "gdal/proj/src/PJ_stere.c"
Import "gdal/proj/src/PJ_sterea.c"
Import "gdal/proj/src/PJ_aea.c"
Import "gdal/proj/src/PJ_bipc.c"
Import "gdal/proj/src/PJ_bonne.c"
Import "gdal/proj/src/PJ_eqdc.c"
Import "gdal/proj/src/PJ_imw_p.c"
Import "gdal/proj/src/PJ_krovak.c"
Import "gdal/proj/src/PJ_lcc.c"
Import "gdal/proj/src/PJ_poly.c"
Import "gdal/proj/src/PJ_rpoly.c"
Import "gdal/proj/src/PJ_sconics.c"
Import "gdal/proj/src/proj_rouss.c"
Import "gdal/proj/src/PJ_cass.c"
Import "gdal/proj/src/PJ_cc.c"
Import "gdal/proj/src/PJ_cea.c"
Import "gdal/proj/src/PJ_eqc.c"
Import "gdal/proj/src/PJ_gall.c"
Import "gdal/proj/src/PJ_labrd.c"
Import "gdal/proj/src/PJ_lsat.c"
Import "gdal/proj/src/PJ_merc.c"
Import "gdal/proj/src/PJ_mill.c"
Import "gdal/proj/src/PJ_ocea.c"
Import "gdal/proj/src/PJ_omerc.c"
Import "gdal/proj/src/PJ_somerc.c"
Import "gdal/proj/src/PJ_tcc.c"
Import "gdal/proj/src/PJ_tcea.c"
Import "gdal/proj/src/PJ_tmerc.c"
Import "gdal/proj/src/PJ_airy.c"
Import "gdal/proj/src/PJ_aitoff.c"
Import "gdal/proj/src/PJ_august.c"
Import "gdal/proj/src/PJ_bacon.c"
Import "gdal/proj/src/PJ_chamb.c"
Import "gdal/proj/src/PJ_hammer.c"
Import "gdal/proj/src/PJ_lagrng.c"
Import "gdal/proj/src/PJ_larr.c"
Import "gdal/proj/src/PJ_lask.c"
Import "gdal/proj/src/PJ_nocol.c"
Import "gdal/proj/src/PJ_ob_tran.c"
Import "gdal/proj/src/PJ_oea.c"
Import "gdal/proj/src/PJ_tpeqd.c"
Import "gdal/proj/src/PJ_vandg.c"
Import "gdal/proj/src/PJ_vandg2.c"
Import "gdal/proj/src/PJ_vandg4.c"
Import "gdal/proj/src/PJ_wag7.c"
Import "gdal/proj/src/PJ_lcca.c"
Import "gdal/proj/src/PJ_geos.c"
Import "gdal/proj/src/PJ_boggs.c"
Import "gdal/proj/src/PJ_collg.c"
Import "gdal/proj/src/PJ_crast.c"
Import "gdal/proj/src/PJ_denoy.c"
Import "gdal/proj/src/PJ_eck1.c"
Import "gdal/proj/src/PJ_eck2.c"
Import "gdal/proj/src/PJ_eck3.c"
Import "gdal/proj/src/PJ_eck4.c"
Import "gdal/proj/src/PJ_eck5.c"
Import "gdal/proj/src/PJ_fahey.c"
Import "gdal/proj/src/PJ_fouc_s.c"
Import "gdal/proj/src/PJ_gins8.c"
Import "gdal/proj/src/PJ_gstmerc.c"
Import "gdal/proj/src/PJ_gn_sinu.c"
Import "gdal/proj/src/PJ_goode.c"
Import "gdal/proj/src/PJ_hatano.c"
Import "gdal/proj/src/PJ_loxim.c"
Import "gdal/proj/src/PJ_mbt_fps.c"
Import "gdal/proj/src/PJ_mbtfpp.c"
Import "gdal/proj/src/PJ_mbtfpq.c"
Import "gdal/proj/src/PJ_moll.c"
Import "gdal/proj/src/PJ_nell.c"
Import "gdal/proj/src/PJ_nell_h.c"
Import "gdal/proj/src/PJ_putp2.c"
Import "gdal/proj/src/PJ_putp3.c"
Import "gdal/proj/src/PJ_putp4p.c"
Import "gdal/proj/src/PJ_putp5.c"
Import "gdal/proj/src/PJ_putp6.c"
Import "gdal/proj/src/PJ_robin.c"
Import "gdal/proj/src/PJ_sts.c"
Import "gdal/proj/src/PJ_urm5.c"
Import "gdal/proj/src/PJ_urmfps.c"
Import "gdal/proj/src/PJ_wag2.c"
Import "gdal/proj/src/PJ_wag3.c"
Import "gdal/proj/src/PJ_wink1.c"
Import "gdal/proj/src/PJ_wink2.c"
Import "gdal/proj/src/pj_latlong.c"
Import "gdal/proj/src/pj_geocent.c"
Import "gdal/proj/src/aasincos.c"
Import "gdal/proj/src/adjlon.c"
Import "gdal/proj/src/bch2bps.c"
Import "gdal/proj/src/bchgen.c"
Import "gdal/proj/src/biveval.c"
Import "gdal/proj/src/dmstor.c"
Import "gdal/proj/src/mk_cheby.c"
Import "gdal/proj/src/pj_auth.c"
Import "gdal/proj/src/pj_deriv.c"
Import "gdal/proj/src/pj_ell_set.c"
Import "gdal/proj/src/pj_ellps.c"
Import "gdal/proj/src/pj_errno.c"
Import "gdal/proj/src/pj_factors.c"
Import "gdal/proj/src/pj_fwd.c"
Import "gdal/proj/src/pj_init.c"
Import "gdal/proj/src/pj_inv.c"
Import "gdal/proj/src/pj_list.c"
Import "gdal/proj/src/pj_malloc.c"
Import "gdal/proj/src/pj_mlfn.c"
Import "gdal/proj/src/pj_msfn.c"
Import "gdal/proj/src/proj_mdist.c"
Import "gdal/proj/src/pj_open_lib.c"
Import "gdal/proj/src/pj_param.c"
Import "gdal/proj/src/pj_phi2.c"
Import "gdal/proj/src/pj_pr_list.c"
Import "gdal/proj/src/pj_qsfn.c"
Import "gdal/proj/src/pj_strerrno.c"
Import "gdal/proj/src/pj_tsfn.c"
Import "gdal/proj/src/pj_units.c"
Import "gdal/proj/src/pj_zpoly1.c"
Import "gdal/proj/src/rtodms.c"
Import "gdal/proj/src/vector1.c"
Import "gdal/proj/src/pj_release.c"
Import "gdal/proj/src/pj_gauss.c"
Import "gdal/proj/src/nad_cvt.c"
Import "gdal/proj/src/nad_init.c"
Import "gdal/proj/src/nad_intr.c"
Import "gdal/proj/src/emess.c"
Import "gdal/proj/src/pj_apply_gridshift.c"
Import "gdal/proj/src/pj_datums.c"
Import "gdal/proj/src/pj_datum_set.c"
Import "gdal/proj/src/pj_transform.c"
Import "gdal/proj/src/geocent.c"
Import "gdal/proj/src/pj_utils.c"
Import "gdal/proj/src/pj_gridinfo.c"
Import "gdal/proj/src/pj_gridlist.c"


Import "*.h"
Import "glue.cpp"


