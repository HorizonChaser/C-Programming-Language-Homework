_BOOL8 __fastcall checkFlag(__int64 flag)
{
  int pos; // [rsp+Ch] [rbp-Ch]
  int flagContentOffset; // [rsp+10h] [rbp-8h]
  int v4; // [rsp+14h] [rbp-4h]

  pos = 0;
  flagContentOffset = 5;                        // flag开头固定为actf{, content偏移为5
  v4 = 0;
  while ( map[pos] != 0x21 )
  {
    pos -= v4;
    if ( *(_BYTE *)(flagContentOffset + flag) != 'W' || v4 == -16 )
    {
      if ( *(_BYTE *)(flagContentOffset + flag) != 'E' || v4 == 1 )
      {
        if ( *(_BYTE *)(flagContentOffset + flag) != 'M' || v4 == 16 )
        {
          if ( *(_BYTE *)(flagContentOffset + flag) != 'J' || v4 == -1 )
            return 0LL;
          v4 = -1;
        }
        else
        {
          v4 = 16;
        }
      }
      else
      {
        v4 = 1;
      }
    }
    else
    {
      v4 = -16;
    }
    ++flagContentOffset;
    while ( !map[pos] )
    {
      if ( v4 == -1 && (pos & 0xF) == 0 )
        return 0LL;
      if ( v4 == 1 && pos % 16 == 15 )
        return 0LL;
      if ( v4 == 16 && (unsigned int)(pos - 240) <= 0xF )
        return 0LL;
      if ( v4 == -16 && (unsigned int)(pos + 15) <= 0x1E )
        return 0LL;
      pos += v4;
    }
  }
  return *(_BYTE *)(flagContentOffset + flag) == '}';
}