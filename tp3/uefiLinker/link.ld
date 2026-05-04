SECTIONS
{
    . = 0x7c00;                 /* Dirección de carga de la BIOS */
    .text :
    {
        *(.text)                /* Todo el código aquí */
        . = 0x1FE;              /* Ir al final del sector (byte 510) */
        SHORT(0xAA55)           /* Firma de arranque obligatoria */
    }
}