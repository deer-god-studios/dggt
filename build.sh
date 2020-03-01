#!/bin/zsh

. .project/dggt.project

TARGET=$1
if [ -z $TARGET ]; then
	TARGET=mem
fi

if has_source_files $TARGET; then
	SRCS=(`get_source_list $TARGET`)
	OBJS=(`get_obj_list $TARGET`)
	OUT=(`get_module_output $TARGET`)

	${CC} ${CC_FLAGS} ${SRCS}
	${CC} ${LINKER_FLAGS} ${OUT} ${OBJS}
fi
