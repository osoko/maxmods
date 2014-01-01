' Copyright 2008-2014 Bruce A Henderson
'
' Licensed under the Apache License, Version 2.0 (the "License");
' you may not use this file except in compliance with the License.
' You may obtain a copy of the License at
'
'     http://www.apache.org/licenses/LICENSE-2.0
'
' Unless required by applicable law or agreed to in writing, software
' distributed under the License is distributed on an "AS IS" BASIS,
' WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
' See the License for the specific language governing permissions and
' limitations under the License.
'
SuperStrict

Import BRL.Blitz
Import BaH.leptonica

Import "../leptonica.mod/src/*.h"

Import "src/*.h"
Import "src/api/*.h"
Import "src/ccstruct/*.h"
Import "src/ccutil/*.h"
Import "src/cube/*.h"
Import "src/neural_networks/runtime/*.h"
Import "src/viewer/*.h"
Import "src/image/*.h"
Import "src/classify/*.h"
Import "src/dict/*.h"
Import "src/cutil/*.h"
Import "src/textord/*.h"
Import "src/pageseg/*.h"
Import "src/ccmain/*.h"
Import "src/wordrec/*.h"

?win32
Import "src/win32/*.h"
Import "src/win32/strtok.cpp"
?

Import "src/api/baseapi.cpp"
Import "src/api/tesseractmain.cpp"

Import "src/ccmain/adaptions.cpp"
Import "src/ccmain/applybox.cpp"
Import "src/ccmain/control.cpp"
Import "src/ccmain/cube_control.cpp"
Import "src/ccmain/cube_reco_context.cpp"
Import "src/ccmain/cubeclassifier.cpp"
Import "src/ccmain/docqual.cpp"
Import "src/ccmain/equationdetect.cpp"
Import "src/ccmain/fixspace.cpp"
Import "src/ccmain/fixxht.cpp"
Import "src/ccmain/imgscale.cpp"
Import "src/ccmain/ltrresultiterator.cpp"
Import "src/ccmain/osdetect.cpp"
Import "src/ccmain/output.cpp"
Import "src/ccmain/pageiterator.cpp"
Import "src/ccmain/pagesegmain.cpp"
Import "src/ccmain/pagewalk.cpp"
Import "src/ccmain/paragraphs.cpp"
Import "src/ccmain/paramsd.cpp"
Import "src/ccmain/pgedit.cpp"
Import "src/ccmain/recogtraining.cpp"
Import "src/ccmain/reject.cpp"
Import "src/ccmain/resultiterator.cpp"
Import "src/ccmain/scaleimg.cpp"
Import "src/ccmain/tessbox.cpp"
Import "src/ccmain/tessedit.cpp"
Import "src/ccmain/tesseract_cube_combiner.cpp"
Import "src/ccmain/tesseractclass.cpp"
Import "src/ccmain/tessvars.cpp"
Import "src/ccmain/tfacepp.cpp"
Import "src/ccmain/thresholder.cpp"
Import "src/ccmain/werdit.cpp"

Import "src/ccstruct/blobbox.cpp"
Import "src/ccstruct/blobs.cpp"
Import "src/ccstruct/blread.cpp"
Import "src/ccstruct/boxread.cpp"
Import "src/ccstruct/boxword.cpp"
'
Import "src/ccstruct/ccstruct.cpp"
Import "src/ccstruct/coutln.cpp"
Import "src/ccstruct/detlinefit.cpp"
Import "src/ccstruct/dppoint.cpp"
Import "src/ccstruct/fontinfo.cpp"
Import "src/ccstruct/genblob.cpp"
Import "src/ccstruct/linlsq.cpp"
Import "src/ccstruct/matrix.cpp"
Import "src/ccstruct/mod128.cpp"
Import "src/ccstruct/normalis.cpp"
Import "src/ccstruct/ocrblock.cpp"
Import "src/ccstruct/ocrpara.cpp"
Import "src/ccstruct/ocrrow.cpp"
Import "src/ccstruct/otsuthr.cpp"
Import "src/ccstruct/pageres.cpp"
Import "src/ccstruct/pdblock.cpp"
Import "src/ccstruct/points.cpp"
Import "src/ccstruct/polyaprx.cpp"
Import "src/ccstruct/polyblk.cpp"
Import "src/ccstruct/publictypes.cpp"
Import "src/ccstruct/quadlsq.cpp"
Import "src/ccstruct/quadratc.cpp"
Import "src/ccstruct/quspline.cpp"
Import "src/ccstruct/ratngs.cpp"
Import "src/ccstruct/rect.cpp"
Import "src/ccstruct/rejctmap.cpp"
Import "src/ccstruct/seam.cpp"
Import "src/ccstruct/split.cpp"
Import "src/ccstruct/statistc.cpp"
Import "src/ccstruct/stepblob.cpp"
Import "src/ccstruct/vecfuncs.cpp"
Import "src/ccstruct/werd.cpp"

Import "src/ccutil/ambigs.cpp"
Import "src/ccutil/basedir.cpp"
Import "src/ccutil/bits16.cpp"
Import "src/ccutil/bitvector.cpp"
Import "src/ccutil/ccutil.cpp"
Import "src/ccutil/clst.cpp"
Import "src/ccutil/elst.cpp"
Import "src/ccutil/elst2.cpp"
Import "src/ccutil/errcode.cpp"
Import "src/ccutil/globaloc.cpp"
Import "src/ccutil/hashfn.cpp"
Import "src/ccutil/indexmapbidi.cpp"
Import "src/ccutil/mainblk.cpp"
Import "src/ccutil/memry.cpp"
Import "src/ccutil/mfcpch.cpp"
Import "src/ccutil/params.cpp"
Import "src/ccutil/serialis.cpp"
Import "src/ccutil/strngs.cpp"
Import "src/ccutil/tessdatamanager.cpp"
Import "src/ccutil/tprintf.cpp"
Import "src/ccutil/unichar.cpp"
Import "src/ccutil/unicharmap.cpp"
Import "src/ccutil/unicharset.cpp"
Import "src/ccutil/unicodes.cpp"

Import "src/classify/adaptive.cpp"
Import "src/classify/adaptmatch.cpp"
Import "src/classify/blobclass.cpp"
Import "src/classify/chartoname.cpp"
Import "src/classify/classify.cpp"
Import "src/classify/cluster.cpp"
Import "src/classify/clusttool.cpp"
Import "src/classify/cutoffs.cpp"
Import "src/classify/extract.cpp"
Import "src/classify/errorcounter.cpp"
Import "src/classify/featdefs.cpp"
Import "src/classify/flexfx.cpp"
Import "src/classify/float2int.cpp"
Import "src/classify/fpoint.cpp"
Import "src/classify/fxdefs.cpp"
Import "src/classify/intfeaturedist.cpp"
Import "src/classify/intfeaturemap.cpp"
Import "src/classify/intfeaturespace.cpp"
Import "src/classify/intfx.cpp"
Import "src/classify/intmatcher.cpp"
Import "src/classify/intproto.cpp"
Import "src/classify/kdtree.cpp"
Import "src/classify/mastertrainer.cpp"
Import "src/classify/mf.cpp"
Import "src/classify/mfdefs.cpp"
Import "src/classify/mfoutline.cpp"
Import "src/classify/mfx.cpp"
Import "src/classify/normfeat.cpp"
Import "src/classify/normmatch.cpp"
Import "src/classify/ocrfeatures.cpp"
Import "src/classify/outfeat.cpp"
Import "src/classify/picofeat.cpp"
Import "src/classify/protos.cpp"
Import "src/classify/sampleiterator.cpp"
Import "src/classify/shapetable.cpp"
Import "src/classify/speckle.cpp"
Import "src/classify/tessclassifier.cpp"
Import "src/classify/trainingsample.cpp"
Import "src/classify/trainingsampleset.cpp"
Import "src/classify/xform2d.cpp"

Import "src/cube/altlist.cpp"
Import "src/cube/beam_search.cpp"
Import "src/cube/bmp_8.cpp"
Import "src/cube/cached_file.cpp"
Import "src/cube/char_altlist.cpp"
Import "src/cube/char_bigrams.cpp"
Import "src/cube/char_samp_enum.cpp"
Import "src/cube/char_samp_set.cpp"
Import "src/cube/char_samp.cpp"
Import "src/cube/char_set.cpp"
Import "src/cube/classifier_factory.cpp"
Import "src/cube/con_comp.cpp"
Import "src/cube/conv_net_classifier.cpp"
Import "src/cube/cube_line_object.cpp"
Import "src/cube/cube_line_segmenter.cpp"
Import "src/cube/cube_object.cpp"
Import "src/cube/cube_search_object.cpp"
Import "src/cube/cube_tuning_params.cpp"
Import "src/cube/cube_utils.cpp"
Import "src/cube/feature_bmp.cpp"
Import "src/cube/feature_chebyshev.cpp"
Import "src/cube/feature_hybrid.cpp"
Import "src/cube/hybrid_neural_net_classifier.cpp"
Import "src/cube/search_column.cpp"
Import "src/cube/search_node.cpp"
Import "src/cube/tess_lang_mod_edge.cpp"
Import "src/cube/tess_lang_model.cpp"
Import "src/cube/word_altlist.cpp"
Import "src/cube/word_list_lang_model.cpp"
Import "src/cube/word_size_model.cpp"
Import "src/cube/word_unigrams.cpp"

Import "src/cutil/bitvec.cpp"
Import "src/cutil/callcpp.cpp"
Import "src/cutil/cutil_class.cpp"
Import "src/cutil/cutil.cpp"
Import "src/cutil/danerror.cpp"
Import "src/cutil/efio.cpp"
Import "src/cutil/emalloc.cpp"
Import "src/cutil/freelist.cpp"
Import "src/cutil/listio.cpp"
Import "src/cutil/oldheap.cpp"
Import "src/cutil/oldlist.cpp"
Import "src/cutil/structures.cpp"
Import "src/cutil/tessarray.cpp"

Import "src/dict/context.cpp"
Import "src/dict/dawg.cpp"
Import "src/dict/dict.cpp"
Import "src/dict/hyphen.cpp"
Import "src/dict/permdawg.cpp"
Import "src/dict/permute.cpp"
Import "src/dict/states.cpp"
Import "src/dict/stopper.cpp"
Import "src/dict/trie.cpp"

Import "src/image/image.cpp"
Import "src/image/imgs.cpp"
Import "src/image/imgtiff.cpp"
Import "src/image/svshowim.cpp"

Import "src/neural_networks/runtime/input_file_buffer.cpp"
Import "src/neural_networks/runtime/neural_net.cpp"
Import "src/neural_networks/runtime/neuron.cpp"
Import "src/neural_networks/runtime/sigmoid_table.cpp"

Import "src/textord/alignedblob.cpp"
Import "src/textord/bbgrid.cpp"
Import "src/textord/blkocc.cpp"
Import "src/textord/blobgrid.cpp"
Import "src/textord/ccnontextdetect.cpp"
Import "src/textord/cjkpitch.cpp"
Import "src/textord/colfind.cpp"
Import "src/textord/colpartition.cpp"
Import "src/textord/colpartitiongrid.cpp"
Import "src/textord/colpartitionset.cpp"
Import "src/textord/devanagari_processing.cpp"
Import "src/textord/drawedg.cpp"
Import "src/textord/drawtord.cpp"
Import "src/textord/edgblob.cpp"
Import "src/textord/edgloop.cpp"
Import "src/textord/equationdetectbase.cpp"
Import "src/textord/fpchop.cpp"
Import "src/textord/gap_map.cpp"
Import "src/textord/imagefind.cpp"
Import "src/textord/linefind.cpp"
Import "src/textord/makerow.cpp"
Import "src/textord/oldbasel.cpp"
Import "src/textord/pithsync.cpp"
Import "src/textord/pitsync1.cpp"
Import "src/textord/scanedg.cpp"
Import "src/textord/sortflts.cpp"
Import "src/textord/strokewidth.cpp"
Import "src/textord/tabfind.cpp"
Import "src/textord/tablefind.cpp"
Import "src/textord/tablerecog.cpp"
Import "src/textord/tabvector.cpp"
Import "src/textord/textlineprojection.cpp"
Import "src/textord/textord.cpp"
Import "src/textord/topitch.cpp"
Import "src/textord/tordmain.cpp"
Import "src/textord/tospace.cpp"
Import "src/textord/tovars.cpp"
Import "src/textord/underlin.cpp"
Import "src/textord/wordseg.cpp"
Import "src/textord/workingpartset.cpp"

Import "src/viewer/scrollview.cpp"
Import "src/viewer/svutil.cpp"
Import "src/viewer/svmnode.cpp"
Import "src/viewer/svpaint.cpp"

Import "src/wordrec/associate.cpp"
Import "src/wordrec/bestfirst.cpp"
Import "src/wordrec/chop.cpp"
Import "src/wordrec/chopper.cpp"
Import "src/wordrec/closed.cpp"
Import "src/wordrec/drawfx.cpp"
Import "src/wordrec/findseam.cpp"
Import "src/wordrec/gradechop.cpp"
Import "src/wordrec/heuristic.cpp"
Import "src/wordrec/language_model.cpp"
Import "src/wordrec/makechop.cpp"
Import "src/wordrec/matchtab.cpp"
Import "src/wordrec/olutil.cpp"
Import "src/wordrec/outlines.cpp"
Import "src/wordrec/pieces.cpp"
Import "src/wordrec/plotedges.cpp"
Import "src/wordrec/plotseg.cpp"
Import "src/wordrec/render.cpp"
Import "src/wordrec/segsearch.cpp"
Import "src/wordrec/tface.cpp"
Import "src/wordrec/wordclass.cpp"
Import "src/wordrec/wordrec.cpp"

Import "glue.cpp"

