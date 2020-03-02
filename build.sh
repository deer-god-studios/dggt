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
	CC_FLAGS=(`get_cc_flags $TARGET`)
	LINKER_FLAGS=(`get_linker_flags $TARGET`)
	LINKED_LIBS=(`get_linked_libs $TARGET`)
	TYPE=$(get_module_type $TARGET)
	echo "${CC} ${CC_FLAGS} ${SRCS} ${LINKED_LIBS}"
	echo "${CC} ${LINKER_FLAGS} ${OUT} ${OBJS}"

	if [[ $TYPE == LIB ]]; then
		${CC} ${CC_FLAGS} ${SRCS}
		${CC} ${LINKER_FLAGS} ${OUT} ${OBJS} ${LINKED_LIBS}
	elif [[ $TYPE == APP ]]; then
		${CC} ${CC_FLAGS} ${LINKER_FLAGS} ${OUT} ${SRCS} ${LINKED_LIBS}
	fi
fi
