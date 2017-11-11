/*
 * File:     stopErr.c 
 * Purpose:  Ends evolution if parents or offsprings are not valid.
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
#include "stopErr.h"



#define STOP_ERR_KEY "stopErr"



int stopErr_init( ModuleTableEntry *self, int msgc, char *msgv[] )
{
    MODULE_KEY( STOP_ERR_KEY );

    SEL_MSG( msgv[0] )

    MSG_CASE( GENERAL_INIT   ) { /* nothing to do */ }
    MSG_CASE( GENERAL_EXIT   ) { /* nothing to do */ }
    MSG_CASE( EVOLUTION_INIT ) { /* nothing to do */ }
    
    END_MSG;

    return( INIT_USED );
}


int stopErr_work( PopID *parents, PopID *offsprings, PopID *ref )
{
    if(    kpm_validPopID( *parents    ) == KPM_NO_ERROR
        && kpm_validPopID( *offsprings ) == KPM_NO_ERROR  )
    return( FALSE );      /* seems to be all right */

    else return( TRUE );  /* there's something gone wrong with the pops! */
}


char *stopErr_errMsg( int err_code )
{
    return( "Evolution stopped by " STOP_ERR_KEY "!" );
}
