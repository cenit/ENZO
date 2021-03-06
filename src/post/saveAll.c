/*
 * File:    (%W%    %G%)
 * Purpose: routines for saving all networks 
 *
 *    
 *           #######     #     #     #######      #####  
 *           #           ##    #          #      #     #
 *           #           # #   #         #       #     #
 *           ######      #  #  #        #        #     #
 *           #           #   # #       #         #     #
 *           #           #    ##      #          #     #
 *           #######     #     #     #######      #####
 *
 *             ( Evolutionaerer NetZwerk Optimierer )
 *
* Implementation:   1.0
 *               adapted to:       SNNSv4.0    
 *
 *                      Copyright (c) 1994 - 1995
 *      Institut fuer Logik, Komplexitaet und Deduktionssysteme
 *                        Universitaet Karlsruhe 
 *
 * Authors: Johannes Schaefer, Matthias Schubert, Thomas Ragg
 * Release: 1.0, August 1995 
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose is hereby granted without fee, provided
 * that the above copyright notice, author statement and this permission
 * notice appear in all copies of this software and related documentation.
 *
 * THE SOFTWARE IS PROVIDED "AS-IS" AND WITHOUT WARRANTY OF ANY KIND, EXPRESS,
 * IMPLIED OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
 *
 * IN NO EVENT SHALL THE INSTITUTE OF LOGIC, COMPLEXITY AND DEDUCTION SYSTEMS OR
 * THE UNIVERSITY OF KARSLRUHE BE LIABLE FOR ANY SPECIAL, INCIDENTAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OF ANY KIND, OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER OR NOT ADVISED OF THE POSSIBILITY OF
 * DAMAGE, AND ON ANY THEORY OF LIABILITY, ARISING OUT OF OR IN CONNECTION WITH
 * THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 *
 *      date        | author          | description                          
 *    --------------+-----------------+------------------------------------  
 *      dd. mon. yy | name of author  | Short description of changes made.   
 *                  | (initials)      | Mark changed parts with initials.    
 *                  |                 |                                      
 *                                                                           
 */                                                                           


#include "enzo.h"
#include "saveAll.h"

#define SAVE_ALL_KEY  "saveAll"
#define NET_DEST_NAME "netDestName"
#define NET_SAVE_CNT  "saveNetsCnt"
#define MARK_DEAD     "markDeadInputs"



#define NO_NAME_WARNING -1
#define NO_NAME_ERR      2
/* the higher err_codes correspond to file numbers ... */

#define DEAD_STRING "xxx"


static char *destName       = NULL;
static int   saveNetsCnt    = 99;
static int   markDeadInputs = TRUE;


int saveAll_init( ModuleTableEntry *self, int msgc, char *msgv[] )
{
    MODULE_KEY( SAVE_ALL_KEY );
    
    SEL_MSG( msgv[0] )

    MSG_CASE( GENERAL_INIT    ) { /* nothing to do */ }
    MSG_CASE( GENERAL_EXIT    ) { /* nothing to do */ }
    MSG_CASE( EVOLUTION_INIT  ) { /* nothing to do */ }
    
    MSG_CASE( NET_DEST_NAME   ) { if( msgc > 1 )
				      destName = strdup( msgv[1] );
				  else
				      return( NO_NAME_WARNING );
			        }
    MSG_CASE( NET_SAVE_CNT    ) { if( msgc > 1 )
				      saveNetsCnt = atoi( msgv[1] );
			        }
    MSG_CASE( MARK_DEAD       ) { if( msgc > 1 )
				      markDeadInputs = FLAG_VALUE( msgv[1] );
			        }
    END_MSG;
    
    return( INIT_USED );
}


int saveAll_work( PopID *parents, PopID *offsprings, PopID *ref )
{
    int cnt = 0, u;
    NetID net;
    char filename[MAX_FILENAME_LEN];

    if( !destName )
        return( MODULE_NO_ERROR );  /* there was a warning during init */
    
    net = kpm_popFirstMember ( *ref );
    sprintf( filename, "%s_ref.net", destName );
    if( kpm_saveNet( net, filename, "reference" ) != KPM_NO_ERROR )
	/* do something */;

    /* --- this would be nice if it worked ---
    kpm_sortNets( subul_netcmp );
    kpm_popFirstMember( *parents );
    ksh_setUpdateFunc(DEFAULT_UPDATE_FUNC);
    ksh_saveResult( "result_snns", TRUE, 1, 10, FALSE, TRUE );
    --- */

    FOR_ALL_PARENTS( net )
    {
	if( cnt > saveNetsCnt ) break;

	if( markDeadInputs )
	{
 	    for( u = ksh_getFirstUnit(); u != 0; u = ksh_getNextUnit() )
	    {
		if( subul_deadInputUnit( u ) )
		{
		    ksh_setUnitName( u, DEAD_STRING );
		}
	    }
	}
	
	sprintf( filename, "%s_%04d.net", destName, cnt++ );
	
	if( kpm_saveNet( net, filename, "parent" ) != KPM_NO_ERROR )
	    return( cnt+3 );
    }

    FOR_ALL_OFFSPRINGS( net )
    {
	sprintf( filename, "%s_%04d.net", destName, cnt++ );
	
	if( kpm_saveNet( net, filename, "offspring" ) != KPM_NO_ERROR )
	    return( cnt+3 );
    }

			
    return( MODULE_NO_ERROR );
}


char *saveAll_errMsg( int err_code )
{
    static char msg[MAX_ERR_MSG_LEN]; /* TR: 13.08.95:  if pointer is returned, should be static ! */
  
    
    char *err_msg[] =
    {"no error", "unknown error",
     "no destination name specified", "can't open output-file %d"};

    if( err_code > NO_NAME_ERR )
    {
	sprintf( msg, err_msg[3], err_code-3 );
	return( msg );
    }
    else if( err_code < 0 )
    {
	return( err_msg[2] );  /* now used as a warning */
    }
    else return( err_msg[err_code] );
    
}
