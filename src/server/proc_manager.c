


#include <stdbool.h>
#include <proc/readproc.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

#include "proc_manager.h"
#include "dbg.h"




pid_t CheckRuningProc(const char * procName)
{
	PROCTAB *procTable = openproc(PROC_FILLSTAT | PROC_FILLSTATUS | PROC_FILLCOM);

	if(!procTable)
	{
		Log(Err, "Failed to create process table!");
		perror("openproc");
		return false;
	}
	else
	{
		proc_t *proc;

		while ((proc = readproc(procTable, NULL)) != NULL) {
      if (strcmp(proc->cmd, procName) == 0) {
        Log(Info, "Process '%s' is running (PID: %d)\n", procName, proc->tid);
        return proc -> tid;
        freeproc(proc);
        closeproc(procTable);
        return true;
      }
      freeproc(proc);
	  }
  }
  return NULL;
}
