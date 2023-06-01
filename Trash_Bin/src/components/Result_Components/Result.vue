<script lang="ts">
import { defineComponent } from 'vue';
import Folder from '../MyFiles_Components/Folder.vue';
import {Types} from '../../types'
    export default defineComponent ({
        props: {
            data: Types.Folder
        },
        components: {
            Folder
        }
    })
</script>

<template>
    <h4>Result</h4>
    <Folder :folder="data"/>
</template>