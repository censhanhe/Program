#ifndef 	__PROMETHEUS_H__
#define 	__PROMETHEUS_H__

#include "../GAIA/gaia.h"
#include "../DWARFS/MISC/cmdparam.h"
#include "../DWARFS/MISC/textline.h"

#include "prom_sysconfig.h"
#include "prom_common.h"
#include "prom_error.h"
#include "prom_directionalfreelink.h"
#include "prom_base.h"

#include "prom_context.h"
#include "prom_context_empty.h"
#include "prom_context_sourcecommand.h"
#include "prom_context_commandparam.h"
#include "prom_context_file.h"
#include "prom_context_filecodeline.h"
#include "prom_context_filecodelineprepare.h"
#include "prom_context_filestructure.h"
#include "prom_context_objctn.h"
#include "prom_context_word.h"

#include "prom_pipeline.h"
#include "prom_pipeline_commandanalyze.h"
#include "prom_pipeline_help.h"
#include "prom_pipeline_filecollect.h"
#include "prom_pipeline_linecollect.h"
#include "prom_pipeline_linebreakcorrect.h"
#include "prom_pipeline_format.h"
#include "prom_pipeline_lineprepare.h"
#include "prom_pipeline_filestructureanalyze.h"
#include "prom_pipeline_objanalyzebase.h"
#include "prom_pipeline_objanalyzeunwrapmacro.h"
#include "prom_pipeline_linestat.h"
#include "prom_pipeline_wordstat.h"
#include "prom_pipeline_symbolstat.h"
#include "prom_pipeline_singlelineanalyze.h"
#include "prom_pipeline_save.h"

#include "prom_pipeline_dispatch.h"
#include "prom_main.h"

#endif
