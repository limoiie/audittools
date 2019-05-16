set_target_properties( 
	clang-format clang-format-check clang-format-diff
	inproc_lat inproc_thr libzmq libzmq-static
	local_lat local_thr remote_lat remote_thr
	PROPERTIES FOLDER ext/zmq
)